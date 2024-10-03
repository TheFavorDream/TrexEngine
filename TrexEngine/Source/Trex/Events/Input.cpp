#include "Input.h"

namespace TrexEngine
{

	Keyboard Input::keyboard;

	TX_API void Input::PollEvents()
	{
		glfwPollEvents();
	}
};