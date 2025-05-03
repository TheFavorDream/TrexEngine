
#include "Mouse.h"

namespace TrexEngine
{
	TX_API double Mouse::MouseX = 0;
	TX_API double Mouse::MouseY = 0;
	TX_API int	  Mouse::LeftButtonState = MS_RELEASE;
	TX_API int	  Mouse::RightButtonState = MS_RELEASE;


	TX_API void Mouse::SetMouseCallBacks(GLFWwindow * p_window)
	{
		glfwSetCursorPosCallback(p_window, Mouse::CursorPositionCallBack);
		glfwSetMouseButtonCallback(p_window, Mouse::MouseClickCallBack);
		return;
	}

	TX_API void Mouse::MouseClickCallBack(GLFWwindow * window, int button, int action, int mods)
	{
		switch (button)
		{
		case TX_MOUSE_BUTTON_LEFT:
			LeftButtonState = action;
			break;
		case TX_MOUSE_BUTTON_RIGHT:
			RightButtonState = action;
			break;
		}
		return;
	}

	TX_API void Mouse::CursorPositionCallBack(GLFWwindow * window, double xpos, double ypos)
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

	TX_API void Mouse::ResetRightButton()
	{
		RightButtonState = KEY_NONE;
	}

	TX_API void Mouse::ResetLeftButton()
	{
		LeftButtonState = KEY_NONE;
	}

	TX_API bool Mouse::IsRightClickPressed()
	{
		return (RightButtonState == MS_PRESS);
	}
	TX_API bool Mouse::IsLeftClickPressed()
	{
		return (LeftButtonState == MS_PRESS);
	}


	TX_API bool Mouse::IsRightClickRelease()
	{
		int State = RightButtonState;

		return (State == MS_RELEASE) ? true : false;
	}
	TX_API bool Mouse::IsLeftClickRelease()
	{
		int State = LeftButtonState;

		return (State == MS_RELEASE) ? true : false;
	}

	TX_API int Mouse::GetKeyState(int pKey)
	{
		switch (pKey)
		{
		case TX_MOUSE_BUTTON_LEFT:
			return LeftButtonState;
		case TX_MOUSE_BUTTON_RIGHT:
			return RightButtonState;
		}
		return -1;
	}

	TX_API void Mouse::GetCursorPosition(GLFWwindow * window, double * Mx, double * My)
	{
		glfwGetCursorPos(window, Mx, My);
	}

	TX_API void Mouse::DisableCursor(GLFWwindow* pwindow, bool Enable)
	{
		switch (Enable)
		{
		case true:
			glfwSetInputMode(pwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		case false:
			glfwSetInputMode(pwindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		}
	}

	TX_API void Mouse::SetCursorMode(GLFWwindow* pWindow, int Mode)
	{
		switch (Mode)
		{
		case TX_CURSOR_HIDE:
			glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		case TX_CURSOR_SHOW:
			glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		}
	}

	TX_API void Mouse::SetCursorPosition(GLFWwindow* pWindow, int pX, int pY)
	{
		glfwSetCursorPos(pWindow, pX, pY);
	}
};