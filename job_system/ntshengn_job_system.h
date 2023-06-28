#pragma once
#include "ntshengn_job_queue.h"
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <cstdint>

namespace NtshEngn {

	struct JobSharedData {
		JobQueue<std::function<void()>> jobQueue;
		std::condition_variable wakeCondition;
		std::mutex wakeMutex;
		std::atomic<uint32_t> currentJobs;
		std::atomic<bool> running;
	};

	struct JobDispatchArguments {
		uint32_t workerIndex;
		uint32_t jobIndex;
	};

	class JobSystem {
	public:
		JobSystem() {
			m_numThreads = std::max(1u, std::thread::hardware_concurrency());
			m_sharedData.currentJobs.store(0);
			m_sharedData.running.store(true);

			for (uint32_t threadID = 0; threadID < m_numThreads; threadID++) {
				std::thread worker([&m_sharedData = m_sharedData] () {
					std::function<void()> job;

					while (m_sharedData.running.load()) {
						if (m_sharedData.jobQueue.pop_front(job)) {
							job();
							m_sharedData.currentJobs.fetch_sub(1);
						}
						else {
							std::unique_lock<std::mutex> lock(m_sharedData.wakeMutex);
							m_sharedData.wakeCondition.wait(lock);
						}
					}
				});

				worker.detach();
			}
		}

		~JobSystem() {
			m_sharedData.running.store(false);
			for (uint32_t threadID = 0; threadID < m_numThreads; threadID++) {
				m_sharedData.wakeCondition.notify_one();
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

				std::function<void()> dispatchJobForWorker = [workerJobOffset, workerJobEnd, workerIndex, job] () {
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
		JobSharedData m_sharedData;
	};

}