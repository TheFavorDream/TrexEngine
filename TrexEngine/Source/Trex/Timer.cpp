#include "./Include/Timer.h"

namespace TrexEngine
{

	std::chrono::time_point<std::chrono::high_resolution_clock> Timer::s_Start;

	Timer::Timer()
	{
		s_Start = std::chrono::high_resolution_clock::now();
	}

	long double Timer::GetElapsedTime(const std::chrono::time_point<std::chrono::high_resolution_clock>& current)
	{
		return (double)std::chrono::duration_cast<std::chrono::seconds> (current - s_Start).count();
	}

	long double Timer::GetCurrentElapsed()
	{
		return (double) std::chrono::duration_cast<std::chrono::seconds> (std::chrono::high_resolution_clock::now() - s_Start).count();
	}

};