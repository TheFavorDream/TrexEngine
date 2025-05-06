
#include "Timer.h"

namespace TrexEngine
{

	std::chrono::time_point<std::chrono::high_resolution_clock> Timer::s_Start;
	float Timer::m_DeltaTime = 0.0f;
	double Timer::m_LastTime = 0.0;

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



	TX_API void Timer::DeltaTime(double Time)
	{
		double Current = Time;
		m_DeltaTime = float(Current - m_LastTime);
		m_LastTime = Current;
	}

	TX_API float Timer::GetDeltaTime()
	{
		return m_DeltaTime*1000.0f;
	}

};