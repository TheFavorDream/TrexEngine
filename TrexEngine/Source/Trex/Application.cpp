#include "Application.h"
#include "Log.h"

namespace TrexEngine
{

	Engine::Engine(const char* p_Title, int p_Width, int p_Height):
		m_Log("Core")
	{

		//Init the Logging unit
		m_Log.SetInfo("Engine Constructor Called");
		Logger::CoreLogger = &m_Log;


		if (m_Renderer.InitGLFW() > 0) m_Log.GetEvents();

		if (m_Window.InitWindow(p_Title, p_Width, p_Height) > 0) m_Log.GetEvents();
	
		if (m_Renderer.InitGLEW() > 0) m_Log.GetEvents();

	}

	Engine::~Engine()
	{
		Logger::CoreLogger->SetInfo("Engine Desturctor Clalled");
		m_Renderer.Shutdown();
		m_Window.Shutdown();
		Logger::s_Loggers.clear();
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

			for (auto i : Logger::s_Loggers)
			{
				i->GetEvents();
			}
		}
	}


};