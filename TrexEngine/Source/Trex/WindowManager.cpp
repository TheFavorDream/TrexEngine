#include "Include/Renderer/WindowManager.h"
#include "Log.h"

namespace TrexEngine
{


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

		glfwGetFramebufferSize(window, &WidthInPixels, &HeightInPixels);


		glfwMakeContextCurrent(window);

		return 0;
	}

	int WindowManager::Shutdown()
	{
		glfwDestroyWindow(window);
		return 0;
	}

	void WindowManager::SetWindowViewPoint(GLFWwindow* window, int width, int height)
	{

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
		Shutdown();
	}

};