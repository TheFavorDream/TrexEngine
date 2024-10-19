/*


	Written by Voltage (Pooya Alizadeh)
	E-mail: poyavoltage148@gmail.com

	Purpose:
	This file handles the mouse inputing and positioning the mouse.

*/


#pragma once

#include "../Core/Core.h"
#include "../3rdparty/glfw/include/GLFW/glfw3.h"

namespace TrexEngine
{
	class Mouse
	{
	public:

		TX_API static void SetCursorPositionCallBack(GLFWwindow* p_window);

		TX_API static void CursorPositionCakkBack (GLFWwindow* window, double xpos, double ypos);

		TX_API static double GetMouseX();
		TX_API static double GetMouseY();

		TX_API static bool IsRightClickPressed();


	private:
		TX_API static double MouseX;
		TX_API static double MouseY;
	};
};