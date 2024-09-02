#include "./Include/Timer.h"

namespace TrexEngine
{

	std::chrono::time_point<std::chrono::high_resolution_clock> Timer::s_Start;

	Timer::Timer()
	{
		s_Start = std::chrono::high_resolution_clock::now();
	}


	double Timer::GetCurrentElapsed()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::high_resolution_clock::now() - s_Start).count();
	}

};