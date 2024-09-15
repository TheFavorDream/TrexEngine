#include "Include/Renderer/WindowManager.h"
#include "Log.h"

namespace TrexEngine
{

	WindowManager::WindowManager()
	{
		Logger::CoreLogger->SetInfo("Window Contructor Called");
	}

	WindowManager* WindowManager::s_WindowManager;

	TX_API WindowManager * WindowManager::GetInstance()
	{
		if (s_WindowManager == NULL)
		{
			s_WindowManager = new WindowManager;
		}

		return s_WindowManager;
	}

	int WindowManager::InitWindow(const char* p_Title, int p_Width, int p_Height)
	{

		this->Width = p_Width;
		this->Height = p_Height;
		this->Title = p_Title;

		window = glfwCreateWindow(Width, Height, Title, NULL, NULL);


		if (window == NULL)
		{
			Logger::CoreLogger->SetError("Unable to Create Window");
			return 1;
		}

		glfwMakeContextCurrent(window);

		glViewport(0, 0, Width, Height);

		glfwGetFramebufferSize(window, &WidthInPixels, &HeightInPixels);

		glfwSetWindowSizeCallback(window, SetViewportSizeCallBack);

		return 0;
	}

	int WindowManager::Shutdown()
	{
		glfwDestroyWindow(window);
		return 0;
	}



	void WindowManager::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}


	void WindowManager::GetWindowSize(int &Width, int &Height)
	{
		Width = this->Width;
		Height = this->Height;
	}


	WindowManager::~WindowManager()
	{
		Logger::CoreLogger->SetInfo("Window Manager Destructor Called");
		Shutdown();
	}

	void WindowManager::SetViewportSizeCallBack(GLFWwindow * window, int width, int height)
	{
		GLCall(glViewport(0,0,width, height));
	}

};