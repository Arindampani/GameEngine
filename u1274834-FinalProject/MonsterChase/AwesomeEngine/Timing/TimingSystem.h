#pragma once

namespace Engine {
	namespace TimingSystem
	{
		float GetCPUCounterFrequency_ms();
		long GetCurrentCPUCounter();
		float CalcTimeSinceLastCall();

	};// namespace timing systems

}

