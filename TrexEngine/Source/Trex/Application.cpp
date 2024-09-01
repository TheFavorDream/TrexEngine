#include "Application.h"
#include "Log.h"

namespace TrexEngine
{

	Engine::Engine(const char* p_Title, int p_Width, int p_Height):
		m_Log("Core")
	{
		m_Log.SetInfo("Engine Constructor Called");

		Logger::CoreLogger = &m_Log;

		m_Renderer.InitGLFW();

		m_Window.InitWindow(p_Title, p_Width, p_Height);
	
		m_Renderer.InitGLEW();


	}

	Engine::~Engine()
	{
		m_Renderer.Shutdown();
		m_Window.Shutdown();
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

			for (auto &i : Logger::s_Loggers)
				i->PrintMessages();
		}
	}


};