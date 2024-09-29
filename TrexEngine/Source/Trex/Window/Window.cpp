#include "Window.h"
#include "Log.h"

namespace TrexEngine
{

	Window::Window()
	{

	}

	int Window::Init(const char* p_Title, int p_Width, int p_Height)
	{

		this->Width = p_Width;
		this->Height = p_Height;
		this->Title = p_Title;

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


		//Create the main window
		window = glfwCreateWindow(Width, Height, Title, NULL, NULL);


		if (window == NULL)
		{
			Logger::CoreLogger->SetError("Unable to Create Window");
			return 1;
		}

		//Make openGL Context
		glfwMakeContextCurrent(window);

		//Set a Viewport
		glViewport(0, 0, Width, Height);

		glfwGetFramebufferSize(window, &WidthInPixels, &HeightInPixels);


		glfwSetWindowSizeCallback(window, SetViewportSizeCallBack);

		return 0;
	}

	int Window::Shutdown()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return 0;
	}



	void Window::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}


	void Window::GetWindowSize(int &Width, int &Height)
	{
		Width = this->Width;
		Height = this->Height;
	}


	Window::~Window()
	{
		Shutdown();
	}

	void Window::SetViewportSizeCallBack(GLFWwindow * window, int width, int height)
	{
		GLCall(glViewport(0,0,width, height));
	}

};