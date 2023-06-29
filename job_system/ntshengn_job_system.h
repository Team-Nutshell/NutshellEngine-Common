#pragma once
#include "ntshengn_job_queue.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <algorithm>
#include <cstdint>

namespace NtshEngn {

	struct JobSharedData {
		JobQueue<std::function<void()>> jobQueue;
		std::condition_variable wakeCondition;
		std::mutex wakeMutex;
		std::atomic<uint32_t> currentJobs;
		bool running;
	};

	struct JobDispatchArguments {
		uint32_t workerIndex;
		uint32_t jobIndex;
	};

	class JobSystem {
	public:
		void init() {
			m_numThreads = std::max(1u, std::thread::hardware_concurrency());
			m_sharedData.currentJobs.store(0);
			m_sharedData.running = true;

			for (uint32_t threadID = 0; threadID < m_numThreads; threadID++) {
				m_threads.emplace_back([&sharedData = m_sharedData]() {
					std::function<void()> job;

					while (sharedData.running) {
						if (sharedData.jobQueue.pop_front(job)) {
							job();
							sharedData.currentJobs.fetch_sub(1);
						}
						else {
							std::unique_lock<std::mutex> lock(sharedData.wakeMutex);
							sharedData.wakeCondition.wait(lock);
						}
					}
				});
			}
		}

		void destroy() {
			m_sharedData.running = false;
			m_sharedData.wakeCondition.notify_all();
			for (uint32_t threadID = 0; threadID < m_numThreads; threadID++) {
				m_threads[threadID].join();
			}
		}

		void execute(const std::function<void()>& job) {
			m_sharedData.jobQueue.push_back(job);
			
			m_sharedData.currentJobs.fetch_add(1);

			m_sharedData.wakeCondition.notify_one();
		}

		void dispatch(uint32_t jobCount, uint32_t jobsPerWorker, const std::function<void(JobDispatchArguments)>& job) {
			if (jobCount == 0 || jobsPerWorker == 0) {
				return;
			}

			const uint32_t workerCount = (jobCount + jobsPerWorker - 1) / jobsPerWorker;

			m_sharedData.currentJobs.fetch_add(workerCount);

			for (uint32_t workerIndex = 0; workerIndex < workerCount; workerIndex++) {
				const uint32_t workerJobOffset = workerIndex * jobsPerWorker;
				const uint32_t workerJobEnd = std::min(workerJobOffset + jobsPerWorker, jobCount);

				std::function<void()> dispatchJobForWorker = [workerJobOffset, workerJobEnd, workerIndex, job]() {
					JobDispatchArguments dispatchArguments;
					dispatchArguments.workerIndex = workerIndex;

					for (uint32_t jobIndex = workerJobOffset; jobIndex < workerJobEnd; jobIndex++) {
						dispatchArguments.jobIndex = jobIndex;

						job(dispatchArguments);
					}
				};

				m_sharedData.jobQueue.push_back(dispatchJobForWorker);

				m_sharedData.wakeCondition.notify_one();
			}
		}

		bool isBusy() {
			return m_sharedData.currentJobs.load() != 0;
		}
		
		void wait() {
			while (isBusy()) {}
		}

		uint32_t getNumThreads() const {
			return m_numThreads;
		}

	private:
		uint32_t m_numThreads = 0;
		std::vector<std::thread> m_threads;
		JobSharedData m_sharedData;
	};

}