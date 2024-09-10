#pragma once
#include "Core.h"
#include <chrono>

namespace TrexEngine
{


	class Timer
	{
	public:

		TX_API Timer(); 

		TX_API static long double GetElapsedTime(const std::chrono::time_point<std::chrono::high_resolution_clock>& current);
		TX_API static long double GetCurrentElapsed();

	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> s_Start;
	};


};