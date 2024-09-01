#pragma once

#include "Core.h"
#include <queue>
#include <string>
#include <iostream>
#include <vector>

namespace TrexEngine
{

	enum MessageType {ERROR, WARNING, INFO};
	struct Message
	{
		std::string m_Message;
		MessageType m_Type;
	};

	class  Logger 
	{
	public:

		TX_API Logger(std::string p_Profile);
		TX_API ~Logger();

		//void Print();

		TX_API void SetError(const char* p_ErrorMessage);
		TX_API void SetError(const std::string& p_ErrorMessage);

		TX_API void SetWarning(const char* p_WarningMessage);
		TX_API void SetWarning(const std::string& p_WarningMessage);

		TX_API void SetInfo(const char* p_InfoMessage);
		TX_API void SetInfo(const std::string& p_InfoMessage);

		TX_API int PrintMessages();


	private:
		std::string m_Profile;
		std::queue<Message> m_Messages;

	public:
		static Logger*  CoreLogger;
		static std::vector<Logger*> s_Loggers;
	};


};