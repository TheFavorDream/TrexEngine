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


	enum KeyState { RELEASE ,PRESS ,HOLD , NONE};

	struct Key 
	{
		int State;
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

		//When you need to retrive a key's current state call this function
		TX_API int GetKeyState(int Key, bool Restore = true) const;

		TX_API void SetKeyPressCallBack(int Key, void(*CallBackFunction)(void));

		TX_API void SetKeyReleaseCallBack(int Key, void(*CallBackFunction)(void));

		TX_API void SetKeyHoldCallBack(int Key, void(*CallBackFunction)(void));

		//Resets a key state:
		TX_API void SetKeyStateNone(int Key);

		TX_API inline std::unordered_map<int, Key>* Get_KeyTable() { return &Key_Table; }

	public:

		TX_API static std::unordered_map<int, Key> Key_Table;

	};

};
