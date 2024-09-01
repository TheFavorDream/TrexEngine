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
		for (int  i =  0 ; i < m_Messages.size() ; ++i)
			m_Messages.pop();
	}


	void Logger::SetError(const char* p_ErrorMessage)
	{
		if (p_ErrorMessage == NULL)
			return;

		m_Messages.push({std::string(p_ErrorMessage), ERROR});
	}

	void Logger::SetError(const std::string& p_ErrorMessage)
	{
		m_Messages.push({ p_ErrorMessage , ERROR });
	}

	void Logger::SetWarning(const char* p_WarningMessage)
	{
		if (p_WarningMessage == NULL)
			return;

		m_Messages.push({ std::string(p_WarningMessage), WARNING });
	}

	void Logger::SetWarning(const std::string& p_WarningMessage)
	{
		m_Messages.push({ std::string(p_WarningMessage), WARNING });

	}

	void Logger::SetInfo(const char* p_InfoMessage)
	{
		if (p_InfoMessage == NULL)
			return;

		m_Messages.push({ std::string(p_InfoMessage), INFO });
	
	}

	void Logger::SetInfo(const std::string& p_InfoMessage)
	{

		m_Messages.push({ std::string(p_InfoMessage), INFO });

	}

	int Logger::PrintMessages()
	{
		if (m_Messages.size() < 1)
			return 0;

		Message& current = m_Messages.front();
		std::string Type;

		switch (current.m_Type)
		{
		case ERROR:		Type = "[Error]";		    break;
		
		case WARNING:	Type = "[Warning]";			break;

		case INFO:		Type = "[Info]";			break;
		}

		std::cout << '[' << m_Profile << ']' << Type << current.m_Message << '\n';

		m_Messages.pop();
		return m_Messages.size();
	}



};