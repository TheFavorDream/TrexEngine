/*


	Written by Voltage.
	E-mail: poyavoltage148@gmail.com

	Purpose:
		Handle Keyboard events such as key pressed, released, held down, Text input.
		This Class is used by input.h file and TrexEngine::Input class.

*/

#pragma once

#include "../Core/Core.h"
#include "../3rdparty/glfw/include/GLFW/glfw3.h"
#include "../Debug/Log.h"
#include "Keys.h"

#include <unordered_map>
#include <queue>

namespace TrexEngine
{


	//Key States 
	enum KeyState {NONE=-1, RELEASE , PRESS , HOLD};

	//A Structure for storing the State and Call Back functions
	struct Key 
	{
		int State = NONE;
		void (*OnPress)(void)   = NULL;
		void (*OnRelease)(void) = NULL;
		void (*OnHold)(void)    = NULL;
	};

	class Keyboard
	{
	public:

		//This sets the KeyCallBack()
		TX_API  void SetKeyCallBack(GLFWwindow* p_window);

		//This will call by glfw every time an event detected:
		TX_API static void KeyCallBack(GLFWwindow* p_window, int key, int scancode, int action, int mode);
		TX_API static void CharacterCallBack(GLFWwindow* p_window, unsigned int codepoint);
		//When you need to retrive a key's current state call this function
		//but don't forget you must call ResetKey() to reset the key state your are checking once you are done.
		TX_API static int GetKeyCurrentState(int Key) ;

		//*Recomended*
		TX_API static void PopTheLastChar();
		TX_API static bool IsKeyPressed(int Key) ;
		TX_API static bool IsKeyReleased(int Key) ;
		TX_API static bool IsKeyHold(int Key) ;

		//Resets the key state to none
		TX_API static void ResetKey(int Key);

		//Set Call back functions to call automatically when any key got pressed, held or released:
		TX_API static void SetKeyPressCallBack(int Key, void(*CallBackFunction)(void));

		TX_API static void SetKeyReleaseCallBack(int Key, void(*CallBackFunction)(void));

		TX_API static void SetKeyHoldCallBack(int Key, void(*CallBackFunction)(void));

		/*
		If you want to get text from user call StartTextInput and pass a string address to it.
		it will read from input (keyboard) and wirte it into string untill you call StopTextInput
		while inputing text, other key events will not be recived so IsKeyXXXX() functions wont work.
		*/

		TX_API static void StartTextInput(std::string& p_Text);
		TX_API static void StopTextInput();

		TX_API static bool IsInputingText() { return IsReadingText; }

		//If Caps Lock Key was on, it returns true.
		TX_API static bool GetCapsLockState();

		//If Num pad was on, it returns true.
		TX_API static bool GetNumPadState();

		//Returns a pointer to key table
		TX_API inline const std::unordered_map<int, Key>* Get_KeyTable() const { return &Key_Table; } 

	public:
		TX_API static std::unordered_map<int, Key> Key_Table;
		TX_API static std::string* Current_String;

		TX_API static bool IsReadingText;

		TX_API static bool IsCapsLockOn;
		TX_API static bool IsNumPadOn;
	};

};
