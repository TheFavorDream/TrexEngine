#pragma once


#include "../Core/Core.h"
#include "../Core/Timer.h"

#include <fstream>
#include <queue>
#include <chrono>
#include <string>
#include <iostream>


#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) Logger::CoreLogger->GL_ClearErrors();\
													  x;ASSERT(Logger::CoreLogger->GL_GetLog(#x, __FILE__, __LINE__));
													

namespace TrexEngine
{

	enum MessageType {TX_ERROR, TX_WARNING, TX_INFO};
	
	//Structure for containing the Log Events info and attrbutes
	struct LogEvent
	{
		MessageType m_Type;
		std::string m_Message;
		std::chrono::time_point<std::chrono::high_resolution_clock> clock;
	};

	//Log System Class
	class  Logger 
	{
	public: //DLL Exports:

		//Constructor 
		TX_API Logger(std::string p_Profile);

		//Should gets Called by Layer Distructor or by defualt gets called by Logger::~Logger()
		TX_API void Shutdown();

		TX_API ~Logger();


		//Set and Print an Error Message on Console
		TX_API void SetError(std::string p_ErrorMessage);

		//Set and Print an Warning Message on Console
		TX_API void SetWarning(std::string p_WarningMessage);

		//Set and Print an Info Message on Console
		TX_API void SetInfo(std::string p_InfoMessage);

		//for opengl debuging:
		//Clears All the Errors from opengl error queue
		TX_API void GL_ClearErrors();

		//Print the information about occured opengl Error
		TX_API bool GL_GetLog(const char* function, const char* file, int line);


	public: // Engine Scope Functions:

		//Writes the LogEvent queue to file
		void WriteLogEvents();

	private: // Internal use:

		//Converts Log type to string
		const char* ToString(MessageType p_Type);

		//pushes the Event on Log queue and prints it on Console.
		void LogMessage(MessageType p_Type, const char* p_Message);


	private:

		std::string m_Profile;
		std::string LogFilePath;
		std::fstream LogFile;

		std::queue<LogEvent> m_Logs;

	public:
		//A refrence to Engine Logger object
		static Logger*  CoreLogger;

		//Stores refrences to created log objects
		static std::vector<Logger*> s_Loggers;
	};


};