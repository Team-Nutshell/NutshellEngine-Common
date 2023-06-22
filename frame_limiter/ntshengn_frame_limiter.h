#pragma once
#include <cstdint>
#include <chrono>

namespace NtshEngn {

	class FrameLimiter {
	public:
		double wait(double dt) {
			if (m_maxFPS != 0) {
				double maxFPSToMilliseconds = 1000.0 / static_cast<double>(m_maxFPS);
				if (dt < maxFPSToMilliseconds) {
					double currentTime = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now().time_since_epoch()).count();
					double busyWaitingNow = currentTime;
					while ((busyWaitingNow - currentTime) < (maxFPSToMilliseconds - dt)) {
						busyWaitingNow = std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now().time_since_epoch()).count();
					}

					return maxFPSToMilliseconds;
				}
			}

			return dt;
		}

		void setMaxFPS(uint32_t maxFPS) {
			m_maxFPS = maxFPS;
		}

		uint32_t getMaxFPS() {
			return m_maxFPS;
		}

	private:
		uint32_t m_maxFPS = 0;
	};

}