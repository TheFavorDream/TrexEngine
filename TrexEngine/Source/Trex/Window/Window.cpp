
#include "Window.h"
#include "Log.h"

namespace TrexEngine
{

	Window::Window():
		IsInited(false), Width(0), Height(0), WidthInPixels(0), HeightInPixels(0)
	{

	}

	int Window::Init()
	{


		//Init the GLFW and Version
		if (!glfwInit())
		{
			Logger::CoreLogger->SetError("Unable to Init GLFW");
			return 1;
		}

		Logger::CoreLogger->SetInfo("Init the GLFW");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		IsInited = true;
		return 0;
	}

	int Window::Shutdown()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return 0;
	}

	TX_API int Window::CreateNewWindow(const char * p_Title, uint32 p_Width, uint32 p_Height)
	{

		this->Width = p_Width;
		this->Height = p_Height;
		this->Title = p_Title;

		if (!IsInited)
		{
			Init();
		}

		//Create the main window
		window = glfwCreateWindow(Width, Height, Title, NULL, NULL);


		if (window == NULL)
		{
			Logger::CoreLogger->SetError("Unable to Create Window");
			return 1;
		}

		Logger::CoreLogger->SetInfo(("Window '" + std::string(Title) +"' Created"));

		//Make openGL Context
		glfwMakeContextCurrent(window);

		//Set a Viewport
		glViewport(0, 0, Width, Height);

		glfwGetFramebufferSize(window, (int*)&WidthInPixels, (int*)&HeightInPixels);


	}



	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}


	TX_API void Window::SetWindowBackground(float x, float y, float z, float a)
	{
		WindowBackGround.x = x;
		WindowBackGround.y = y;
		WindowBackGround.z = z;
		WindowBackGround.a = a;
	}

	void Window::GetWindowSize(uint32 &Width, uint32 &Height)
	{
		Width = this->Width;
		Height = this->Height;
	}


	TX_API void Window::SetWindowSize(uint32 Width, uint32 Height)
	{
		glfwSetWindowSize(window, Width, Height);
	}

	TX_API void Window::SetViewport(uint32 X, uint32 Y, uint32 Width, uint32 Height)
	{
		GLCall(glViewport(X, Y, Width, Height));
		this->Width = Width;
		this->Height = Height;
	}

	TX_API void Window::HideWindow(bool p_Hide)
	{
		switch (p_Hide)
		{
		case true:
			glfwHideWindow(window);
			break;
		case false:
			glfwShowWindow(window);
			break;
		}
	}


	Window::~Window()
	{
		Shutdown();
	}

};