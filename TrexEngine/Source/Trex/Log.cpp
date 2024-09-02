#include "../Include/Log.h"


//Implementation for Logging system:
namespace TrexEngine
{
	Logger*  Logger::CoreLogger = nullptr;
	std::vector<Logger*> Logger::s_Loggers;

	Logger::Logger(std::string p_Profile) : m_Profile(p_Profile)
	{
		s_Loggers.push_back(this);
	}

	Logger::~Logger()
	{
		for (int  i =  0 ; i < m_Events.size() ; ++i)
			m_Events.pop();

	}


	void Logger::SetError(const char* p_ErrorMessage)
	{
		if (p_ErrorMessage == NULL)
			return;

		m_Events.push({ERROR, p_ErrorMessage, std::chrono::system_clock::now()});
	}



	void Logger::SetWarning(const char* p_WarningMessage)
	{
		if (p_WarningMessage == NULL)
			return;

		m_Events.push({ WARNING, p_WarningMessage, std::chrono::system_clock::now() });
	}



	void Logger::SetInfo(const char* p_InfoMessage)
	{
		if (p_InfoMessage == NULL)
			return;

		m_Events.push({ INFO, p_InfoMessage, std::chrono::system_clock::now() });
	
	}


	int Logger::PrintMessages()
	{
		if (m_Events.size() < 1)
			return 0;


		while (!m_Events.empty())
		{
			auto C = m_Events.front();
			time_t ctime = std::chrono::system_clock::to_time_t(C.clock);
			std::cout << '[' << m_Profile << "][" << Timer::GetCurrentElapsed() << "ms][" << ToString(C.m_Type) << ']' << C.m_Message << "\n\n";
			m_Events.pop();
		}

		return (int)m_Events.size();
	}

	const char * Logger::ToString(MessageType type)
	{

		switch (type)
		{
		case ERROR:   return "Error";
		case WARNING: return "Warning";
		case INFO:    return "Info";
		}

		return nullptr;
	}



};