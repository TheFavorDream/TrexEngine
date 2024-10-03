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

#include <queue>

namespace TrexEngine
{

	struct KeyEvent
	{
		int key = -1;
		int scancode = -1;
		int action = -1;
		int mode = -1;
	};

	class Keyboard
	{
	public:

		//This sets the KeyCallBack()
		TX_API static void SetKeyCallBack(GLFWwindow* p_window);

		//This will call by glfw every time an event detected:
		TX_API static void KeyCallBack(GLFWwindow* p_window, int key, int scancode, int action, int mode);

		//check if queue was empty or not
		TX_API static bool KeyQueueEmpty();

		//Returns the first event
		TX_API static KeyEvent Keyboard::GetEvent();

	private:

		TX_API static std::queue<KeyEvent> KeyQueue;
	};

};
