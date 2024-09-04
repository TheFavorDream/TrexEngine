#include "../Include/Log.h"


//Implementation for Logging system:
namespace TrexEngine
{
	Logger*  Logger::CoreLogger = nullptr;
	std::vector<Logger*> Logger::s_Loggers;

	Logger::Logger(std::string p_Profile) : m_Profile(p_Profile)
	{
		s_Loggers.push_back(this);
		

		LogFilePath = (m_Profile + "_RuntimeLog.txt");
		LogFile.open(LogFilePath, std::ios::out);

		if (LogFile.fail())
		{
			SetError("Unable to Open Log File");
		}

	}

	Logger::~Logger()
	{

		SetError((m_Profile + " Distructor called"));

		GetEvents();

		for (int  i =  0 ; i < m_Events.size() ; ++i)
			m_Events.pop();

		LogFile.close();

		for (int i = 0; i < s_Loggers.size(); ++i)
		{
			if (s_Loggers[i]->m_Profile == m_Profile)
			{
				s_Loggers.erase(s_Loggers.begin() + i);
			}
		}

	}


	void Logger::SetError(std::string p_ErrorMessage)
	{
		m_Events.push({ERROR, p_ErrorMessage, std::chrono::high_resolution_clock::now()});
	}



	void Logger::SetWarning(std::string p_WarningMessage)
	{
		m_Events.push({ WARNING, p_WarningMessage, std::chrono::high_resolution_clock::now() });
	}



	void Logger::SetInfo(std::string p_InfoMessage)
	{
		m_Events.push({ INFO, p_InfoMessage, std::chrono::high_resolution_clock::now() });
	}


	int Logger::GetEvents()
	{
		if (m_Events.size() < 1)
			return 0;


		while (!m_Events.empty())
		{
			auto C = m_Events.front();
			std::cout << '[' << m_Profile << "][" << Timer::GetElapsedTime(C.clock) << "ms][" << ToString(C.m_Type) << ']' << C.m_Message << "\n\n";
			LogFile << '[' << m_Profile << "][" << Timer::GetElapsedTime(C.clock) << "ms][" << ToString(C.m_Type) << ']' << C.m_Message << "\n\n";
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