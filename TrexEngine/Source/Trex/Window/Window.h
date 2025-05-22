#pragma once

#include "../Core/Core.h"
#include "../3rdparty/GL/glew.h"
#include "../3rdparty/glfw/Include/GLFW/glfw3.h"

namespace TrexEngine
{

	//Tempoary:
	struct vec4
	{
		float x, y, z, a;
	};

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
		TX_API inline const vec4& GetBackground() { return WindowBackGround; }

		TX_API void SwapBuffers();


		TX_API void SetWindowBackground(float x, float y, float z, float a=1.0f);
		TX_API void GetWindowSize(int32 &Width, int32 &Height);
		TX_API void SetWindowSize(uint32 Width, uint32 Height);

		TX_API void SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height);

		TX_API void HideWindow(bool p_Hide);

		//Window Events
		TX_API inline bool WindowShouldClose() const { return glfwWindowShouldClose(window); }

	public:
		static void ViewPortCallBack(GLFWwindow* window, int Width, int Height);
	private:

		bool IsInited = false;

		GLFWwindow* window = NULL;

		uint32 Width = 0;
		uint32 Height = 0;
		
		uint32 WidthInPixels = 0;
		uint32 HeightInPixels = 0;


		vec4 WindowBackGround;

		const char* Title = NULL;

	};

};