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
		case MOUSE_BUTTON_LEFT:
			LeftButtonState = action;
			break;
		case MOUSE_BUTTON_RIGHT:
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
		RightButtonState = NONE;
	}

	TX_API void Mouse::ResetLeftButton()
	{
		LeftButtonState = NONE;
	}

	TX_API bool Mouse::IsRightClickPressed()
	{
		int State = RightButtonState;
		ResetRightButton();
		return (State == MS_PRESS) ? true : false;
	}
	TX_API bool Mouse::IsLeftClickPressed()
	{
		int State = LeftButtonState;
		ResetLeftButton();
		return (State == MS_PRESS) ? true : false;
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
};