#pragma once

#include "../Core/Core.h"
#include "../3rdparty/GL/glew.h"
#include "../3rdparty/glfw/Include/GLFW/glfw3.h"

namespace TrexEngine
{


	class  Window
	{
	public:

		TX_API Window();
		TX_API ~Window();


		TX_API int Init();
		TX_API int Shutdown();

		TX_API int CreateNewWindow(const char* p_Title, uint32 p_Width, uint32 p_Height);

		TX_API inline GLFWwindow* GetWindow() const { return window; }
		TX_API inline const char* GetTitle() const { return Title; }
		TX_API inline int GetW() { return Width; }
		TX_API inline int GetH() { return Height; }

		TX_API void SwapBuffers();

		TX_API void GetWindowSize(uint32 &Width, uint32 &Height);
		TX_API void SetWindowSize(uint32 Width, uint32 Height);

		TX_API void HideWindow(bool p_Hide);

		//Window Events
		TX_API inline bool WindowShouldClose() const { return glfwWindowShouldClose(window); }
	public:
		static void ViewportSizeCallBack(GLFWwindow* window, int32 width, int32 height);
	private:

		bool IsInited = false;

		GLFWwindow* window = NULL;

		uint32 Width = 0;
		uint32 Height = 0;
		
		uint32 WidthInPixels = 0;
		uint32 HeightInPixels = 0;

		const char* Title = NULL;

	};

};