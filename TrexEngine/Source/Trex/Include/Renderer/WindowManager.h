#pragma once

#include "Core.h"
#include "GLFW/glfw3.h"

namespace TrexEngine
{

	class  WindowManager
	{
	public:


		TX_API WindowManager();

		TX_API int InitWindow(const char* p_Title, int p_Width, int p_Height);

		TX_API int Shutdown();


		TX_API inline GLFWwindow* GetWindow() const { return window; }
		TX_API inline const char* GetTitle() const { return Title; }
		TX_API inline bool WindowShouldClose() const { return glfwWindowShouldClose(window); }

		TX_API void SwapBuffers();

		TX_API void GetWindowSize(int &Width, int &Height);

		TX_API ~WindowManager();

	public:

		static void SetViewportSizeCallBack(GLFWwindow* window, int width, int height);

	private:

		GLFWwindow* window = NULL;

		int Width = 0;
		int Height = 0;
		
		int WidthInPixels = 0;
		int HeightInPixels = 0;

		const char* Title = NULL;
	};
};