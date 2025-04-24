
#include "Input.h"

namespace TrexEngine
{

	Keyboard Input::keyboard;
	Mouse	 Input::mouse;

	TX_API void Input::PollEvents()
	{
		glfwPollEvents();
	}
};