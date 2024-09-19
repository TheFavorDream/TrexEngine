#include "../Include/Log.h"

#include "GL/glew.h"
//Implementation for Logging system:
namespace TrexEngine
{
	Logger*  Logger::CoreLogger = nullptr;
	std::vector<Logger*> Logger::s_Loggers;

	Logger::Logger(std::string p_Profile): m_Profile(p_Profile)
	{
		if (p_Profile == "Core")
			CoreLogger = this;

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


		LogFile.close();

		for (int i = 0; i < s_Loggers.size(); ++i)
		{
			if (s_Loggers[i]->m_Profile == m_Profile)
			{
				s_Loggers.erase(s_Loggers.begin() + i);
			}
		}

		if (s_Loggers.empty())
			s_Loggers.clear();

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
		std::cout << '[' << m_Profile <<
			"][" << Timer::GetElapsedTime(std::chrono::high_resolution_clock::now())
			<< "ms]" << ToString(p_Type)  <<
			p_Message << "\n\n";

		LogFile << '[' << m_Profile <<
			"][" << Timer::GetElapsedTime(std::chrono::high_resolution_clock::now())
			<< "ms]" << ToString(p_Type) << 
			p_Message << "\n\n";
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