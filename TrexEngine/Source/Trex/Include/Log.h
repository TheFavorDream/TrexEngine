#pragma once


#include "Core.h"
#include "Timer.h"

#include <fstream>
#include <queue>
#include <chrono>
#include <string>
#include <iostream>
#include <vector>

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) Logger::CoreLogger->GL_ClearErrors();\
													  x;ASSERT(Logger::CoreLogger->GL_GetLog(#x, __FILE__, __LINE__));
													

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

		//for opengl debuging
		TX_API void GL_ClearErrors();

		TX_API bool GL_GetLog(const char* function, const char* file, int line);


	private:

		const char* ToString(MessageType p_Type);

		void LogMessage(MessageType p_Type, const char* p_Message);

	private:

		std::string m_Profile;

		std::string LogFilePath;

		std::fstream LogFile;

	public:
		static Logger*  CoreLogger;
		static std::vector<Logger*> s_Loggers;
	};


};