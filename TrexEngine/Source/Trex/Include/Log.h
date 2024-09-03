#pragma once

#include "Core.h"
#include "Timer.h"

#include <fstream>
#include <queue>
#include <chrono>
#include <string>
#include <iostream>
#include <vector>

namespace TrexEngine
{

	enum MessageType {ERROR, WARNING, INFO};
	
	//Structure for containing the Log Events info and attrbutes
	struct LogEvent
	{
		MessageType m_Type;
		std::string m_Message;
		std::chrono::time_point<std::chrono::high_resolution_clock> clock;
	};

	class  Logger 
	{
	public:

		TX_API Logger(std::string p_Profile);
		TX_API ~Logger();

		//void Print();

		TX_API void SetError(std::string p_ErrorMessage);

		TX_API void SetWarning(std::string p_WarningMessage);

		TX_API void SetInfo(std::string p_InfoMessage);

		TX_API int GetEvents();

	private:

		const char* ToString(MessageType type);

	private:

		std::string m_Profile;

		std::queue<LogEvent> m_Events;

		std::string LogFilePath;

		std::fstream LogFile;

	public:
		static Logger*  CoreLogger;
		static std::vector<Logger*> s_Loggers;
	};


};