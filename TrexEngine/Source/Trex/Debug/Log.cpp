
#include "Log.h"

#include "glew.h"


//Implementation for Logging system:
namespace TrexEngine
{

	Logger*  Logger::CoreLogger = nullptr;

	std::vector<Logger*> Logger::s_Loggers;

	Logger::Logger(std::string p_Profile, bool pUseLogFile, int pLogLevel)
		: m_LogLevel(pLogLevel), m_Profile(p_Profile), m_UseLogFile(pUseLogFile)
	{

		
		if (p_Profile == "Core")
			CoreLogger = this;

		s_Loggers.push_back(this);
		
		//Create or open the log file
		if (m_UseLogFile)
		{
			LogFilePath = (m_Profile + "_RuntimeLog.txt");
			LogFile.open(LogFilePath, std::ios::out | std::ios::trunc);


			if (LogFile.fail())
			{
				SetError("Unable to Open Log File");
			}
		}
	}

	TX_API void Logger::Shutdown()
	{
		if (m_UseLogFile)
			WriteLogEvents();
	}

	Logger::~Logger()
	{

		Shutdown();
		//Closes the Log file
		if (m_UseLogFile)
			LogFile.close();

		//removes this object from vector
		for (int i = 0; i < s_Loggers.size(); ++i)
		{
			if (s_Loggers[i]->m_Profile == m_Profile)
			{
				s_Loggers.erase(s_Loggers.begin() + i);
			}
		}
	}

	TX_API void Logger::ResetLogs()
	{
		m_Logs.clear();
	}


	void Logger::SetError(std::string p_ErrorMessage)
	{
		if (m_LogLevel < TX_L1)
			return;
		LogMessage(TX_ERROR, p_ErrorMessage);
	}



	void Logger::SetWarning(std::string p_WarningMessage)
	{
		if (m_LogLevel < TX_L2)
			return;
		LogMessage(TX_WARNING, p_WarningMessage);
	}



	void Logger::SetInfo(std::string p_InfoMessage)
	{
		if (m_LogLevel < TX_L3)
			return;
		LogMessage(TX_INFO, p_InfoMessage);
	}

	TX_API void Logger::GL_ClearErrors()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	TX_API bool Logger::GL_GetLog(const char * function, const char * file, int line)
	{
		while (GLenum error = glGetError())
		{
			SetError(("[OpenGL]: Code:" + std::to_string(error) + "\tFunction:" + std::string(function) + " Line:" + std::to_string(line) + " File:" + std::string(file)));
			return false;
		}
		return true;
	}

	void Logger::SetLogLevel(uint16 pLevel)
	{
		if (pLevel >= TX_L0 && pLevel <= TX_L3)
			m_LogLevel = pLevel;
	}


	void Logger::LogMessage(MessageType p_Type, const std::string& p_Message)
	{

		//push an log event
		m_Logs.push_back({p_Type, p_Message, Timer::GetCurrentElapsedUint()/1000.0, 0});

		//print
		std::cout << '[' << m_Profile << "][" <<
			Timer::GetCurrentElapsedUint() / 1000 << "s]" <<
			ToString(p_Type)  << p_Message << '\n';
	}

	void Logger::WriteLogEvents()
	{
		while (!m_Logs.empty())
		{
			auto Current = m_Logs.front();
			
			LogFile << '[' << m_Profile <<
				"][" << Timer::GetElapsedTime(std::chrono::high_resolution_clock::now())
				<< "ms]" << ToString(Current.m_Type) <<
				Current.m_Description << "\n";

			m_Logs.pop_back();
		}
	}


	const char * Logger::ToString(MessageType p_Type)
	{

		switch (p_Type)
		{
		case TX_ERROR:   return "[Error]";
		case TX_WARNING: return "[Warning]";
		case TX_INFO:    return "[Info]";
		}

		return nullptr;
	}


};