#include "Mouse.h"

namespace TrexEngine
{
	TX_API double Mouse::MouseX = 0;
	TX_API double Mouse::MouseY = 0;


	TX_API void Mouse::SetCursorPositionCallBack(GLFWwindow * p_window)
	{
		glfwSetCursorPosCallback(p_window, Mouse::CursorPositionCakkBack);
		return;
	}

	TX_API void Mouse::CursorPositionCakkBack(GLFWwindow * window, double xpos, double ypos)
	{
		MouseX = xpos;
		MouseY = ypos;
		return;
	}

	TX_API double Mouse::GetMouseX()
	{
		return MouseX;
	}

	TX_API double Mouse::GetMouseY()
	{
		return MouseY;
	}

	TX_API bool Mouse::IsRightClickPressed()
	{
		return false;
	}
};