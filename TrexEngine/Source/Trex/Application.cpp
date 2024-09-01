#include "Application.h"

namespace TrexEngine
{

	Engine::Engine(const char* p_Title, int p_Width, int p_Height)
	{
		m_Renderer.InitGLFW();

		m_Window.InitWindow(p_Title, p_Width, p_Height);
	
		m_Renderer.InitGLEW();
		
	}

	Engine::~Engine()
	{

	}

	void Engine::run()
	{
		while (!m_Window.WindowShouldClose())
		{
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			Event();

			Update();

			Render();

			m_Window.SwapBuffers();
			glfwPollEvents();
		}
	}


};