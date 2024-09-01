#pragma once

#include "Core.h"
#include "GLFW/glfw3.h"

namespace TrexEngine
{

	class TX_API WindowManager
	{
	public:


		int InitWindow(const char* p_Title, int p_Width, int p_Height);

		int Shutdonw();


		inline GLFWwindow* GetWindow() const { return window; }
		inline const char* GetTitle() const { return Title; }
		inline bool WindowShouldClose() const { return glfwWindowShouldClose(window); }

		void SetWindowViewPoint(GLFWwindow* window, int width, int height);

		void SwapBuffers();

		void GetWindowSize(int &Width, int &Height);

		~WindowManager();

	private:

		GLFWwindow* window = NULL;

		int Width = 0;
		int Height = 0;
		
		int WidthInPixels = 0;
		int HeightInPixels = 0;

		const char* Title = NULL;
	};
};