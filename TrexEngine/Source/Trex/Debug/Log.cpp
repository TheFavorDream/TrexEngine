
#include "Log.h"

#include "glew.h"


//Implementation for Logging system:
namespace TrexEngine
{

	Logger*  Logger::CoreLogger = nullptr;

	std::vector<Logger*> Logger::s_Loggers;

	Logger::Logger(std::string p_Profile, bool UseLogFile)
		: m_Profile(p_Profile), m_UseLogFile(UseLogFile)
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


	void Logger::SetError(std::string p_ErrorMessage)
	{
		LogMessage(TX_ERROR, p_ErrorMessage.c_str());
	}



	void Logger::SetWarning(std::string p_WarningMessage)
	{
		LogMessage(TX_WARNING, p_WarningMessage.c_str());
	}



	void Logger::SetInfo(std::string p_InfoMessage)
	{
		LogMessage(TX_INFO, p_InfoMessage.c_str());
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


	void Logger::LogMessage(MessageType p_Type, const char * p_Message)
	{

		//push an log event
		m_Logs.push({p_Type, p_Message, std::chrono::high_resolution_clock::now()});

		//print
		std::cout << '[' << m_Profile << "][" <<
			Timer::GetElapsedTime(std::chrono::high_resolution_clock::now())<< "ms]" <<
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
				Current.m_Message << "\n";

			m_Logs.pop();
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