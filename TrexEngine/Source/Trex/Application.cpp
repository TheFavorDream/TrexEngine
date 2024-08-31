#include "Application.h"

namespace TrexEngine
{

	Engine::Engine(const char* p_Title, int p_Width, int p_Height)
	{
		m_Renderer.Init();

		m_Window.InitWindow(p_Title, p_Width, p_Height);
	
		
	}

	Engine::~Engine()
	{

	}

	void Engine::run()
	{
		while (!m_Window.WindowShouldClose())
		{

			Event();

			Update();

			Render();


			glfwPollEvents();
		}
	}


};