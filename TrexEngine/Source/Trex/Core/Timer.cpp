#include "Timer.h"

namespace TrexEngine
{

	std::chrono::time_point<std::chrono::high_resolution_clock> Timer::s_Start;

	Timer::Timer()
	{
		s_Start = std::chrono::high_resolution_clock::now();
	}

	long double Timer::GetElapsedTime(const std::chrono::time_point<std::chrono::high_resolution_clock>& current)
	{
		return (double)std::chrono::duration_cast<std::chrono::milliseconds> (current - s_Start).count();
	}

	long double Timer::GetCurrentElapsed()
	{
		return (double) std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::high_resolution_clock::now() - s_Start).count();
	}

	TX_API uint64 Timer::GetCurrentElapsedUint()
	{
		return (uint64) std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::high_resolution_clock::now() - s_Start).count();

	}

};