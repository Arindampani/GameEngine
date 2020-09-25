#include <limits.h>
#include <Windows.h>

#include <assert.h>

#if defined _DEBUG
#define CLAMP_FRAMETIME
#endif

#define DESIRED_FPS			  60.0f
#define DESIRED_FRAMETIME_MS  (1000.0f/ DESIRED_FPS)
#define MAX_FRAMETIME_MS	  (2*DESIRED_FRAMETIME_MS)

namespace Engine {
	namespace TimingSystem {

		float GetCPUCounterFrequency_ms() {

			LARGE_INTEGER performanceFrequency = { 0 };
			bool bSuccess = QueryPerformanceFrequency(&performanceFrequency);

			assert(bSuccess);
			return performanceFrequency.QuadPart;
		}

		long GetCurrentCPUCounter() {
			LARGE_INTEGER performanceCounter = { 0 };

			bool bSucess = QueryPerformanceCounter(&performanceCounter);

			assert(bSucess);

			return performanceCounter.QuadPart;
		}

		float CalcTimeSinceLastCall() {

			static long g_LastFrameStartTick = 0;
			float g_LastFrameTime_ms;

			long currentTick = GetCurrentCPUCounter();

			if (g_LastFrameStartTick) {

				long elapsedTicks = (currentTick - g_LastFrameStartTick);

				g_LastFrameTime_ms = elapsedTicks / GetCPUCounterFrequency_ms();
			}
			else {
				g_LastFrameTime_ms = 13.3; // Assume a 60hz frame for first call
			}

			g_LastFrameStartTick = currentTick;


#if defined(CONSTANT_FRAMETIME)
			return DESIRED_FRAMETIME_MS;
#elif defined(CLAMP_FRAMETIME)
			if (g_LastFrameTime_ms > MAX_FRAMETIME_MS)
				return MAX_FRAMETIME_MS;
			else
				return g_LastFrameTime_ms;
#else
			return g_LastFrameTime_ms;
#endif // defined(CONSTANT_FRAMETIME)

			return g_LastFrameTime_ms;
		}
	}
}

