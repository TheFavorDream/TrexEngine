#include "Keyboard.h"


namespace TrexEngine
{

	TX_API std::queue<KeyEvent> Keyboard::KeyQueue;


	TX_API void Keyboard::SetKeyCallBack(GLFWwindow* p_window) 
	{
		glfwSetKeyCallback(p_window, KeyCallBack);
	}

	TX_API void Keyboard::KeyCallBack(GLFWwindow* p_window, int key, int scancode, int action, int mode)
	{
		
		KeyQueue.push({key, scancode, action, mode});
	}

	TX_API bool Keyboard::KeyQueueEmpty()
	{
		return KeyQueue.empty();
	}

	TX_API KeyEvent Keyboard::GetEvent()
	{
		KeyEvent p_event = KeyQueue.front();
		KeyQueue.pop();
		return p_event;
	}

};