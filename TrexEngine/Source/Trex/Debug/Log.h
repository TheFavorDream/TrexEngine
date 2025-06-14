#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include "../Core/Core.h"
#include "../Core/Timer.h"


//Logging levels
#define TX_L0 0 //Logging Disabled
#define TX_L1 1	//Only Errors
#define TX_L2 2 //Errors and Warnings
#define TX_L3 3 //Errors, Warnings and Information

#define STOP() __debugbreak()
#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) Logger::CoreLogger->GL_ClearErrors();\
													  x;Logger::CoreLogger->GL_GetLog(#x, __FILE__, __LINE__);
													

namespace TrexEngine
{

	enum MessageType {TX_ERROR, TX_WARNING, TX_INFO};
	
	//Structure for containing the Log Events info and attrbutes
	struct LogEvent
	{
		MessageType m_Type;
		std::string m_Description;
		float64 m_Time;
		double m_ErrorCode;
	};

	//Log System Class
	class  Logger 
	{
	public: //DLL Exports:

		//Constructor 
		TX_API Logger(std::string p_Profile, bool pUseLogFile = false, int pLogLevel=TX_L3);

		//Should gets Called by Layer Distructor or by defualt gets called by Logger::~Logger()
		TX_API void Shutdown();

		TX_API ~Logger();

		TX_API void ResetLogs();

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


		TX_API void SetLogLevel(uint16 pLevel);

		TX_API inline std::string& GetProfileName() { return m_Profile; }
		TX_API inline std::vector<LogEvent>& GetLogs() { return m_Logs; }
	public: // Engine Scope Functions:

		//Writes the LogEvent queue to file
		void WriteLogEvents();

	private: // Internal use:

		//Converts Log type to string
		const char* ToString(MessageType p_Type);

		//pushes the Event on Log queue and prints it on Console.
		void LogMessage(MessageType p_Type, const std::string& p_Message);


	private:

		int m_LogLevel;

		std::string m_Profile;
		std::string LogFilePath;
		std::fstream LogFile;

		std::vector<LogEvent> m_Logs;
		bool m_UseLogFile = false;

	public:
		//A refrence to Engine Logger object
		static Logger*  CoreLogger;
		//Stores refrences to created log objects
		TX_API static std::vector<Logger*> s_Loggers;
	};


};