/*


	Written by Voltage (Pooya Alizadeh)
	E-mail: poyavoltage148@gmail.com

	Purpose:
	This file handles the mouse inputing and positioning the mouse.

*/


#pragma once


#include "../Core/Core.h"
#include "../3rdparty/glfw/include/GLFW/glfw3.h"
#include "Keys.h"

#define TX_CURSOR_HIDE 0
#define TX_CURSOR_SHOW 1

namespace TrexEngine
{
	class Mouse
	{
	public:

		TX_API static void SetMouseCallBacks(GLFWwindow* p_window);

		TX_API static void MouseClickCallBack(GLFWwindow* window, int button, int action, int mods);
		TX_API static void CursorPositionCallBack (GLFWwindow* window, double xpos, double ypos);

		TX_API static double GetMouseX();
		TX_API static double GetMouseY();

		TX_API static void ResetRightButton();
		TX_API static void ResetLeftButton();

		TX_API static bool IsRightClickPressed();
		TX_API static bool IsLeftClickPressed();

		TX_API static bool IsRightClickRelease();
		TX_API static bool IsLeftClickRelease();

		TX_API static int GetKeyState(int pKey);

		TX_API static void SetCursorMode(GLFWwindow* pWindow, int Mode);

		TX_API static void SetCursorPosition(GLFWwindow* pWindow, int pX, int pY);

	private:
		TX_API static double MouseX;
		TX_API static double MouseY;


		TX_API static int LeftButtonState;
		TX_API static int RightButtonState;
	};
};