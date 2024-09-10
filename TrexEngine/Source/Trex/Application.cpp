#include "Application.h"
#include "Log.h"

namespace TrexEngine
{

	Engine::Engine(const char* p_Title, int p_Width, int p_Height):
		m_Log("Core"),
		m_Shader("G:\\Dev\\TrexEngine\\TrexEngine\\Source\\Trex\\Include\\Renderer\\Shaders\\Simple.glsl")
	{

		//Init the Logging unit
		m_Log.SetInfo("Engine Constructor Called");


		m_Renderer.InitGLFW();

		m_Window.InitWindow(p_Title, p_Width, p_Height);
	
		m_Renderer.InitGLEW();

		m_Shader.CreateShaderProgram();

	}

	Engine::~Engine()
	{
		Logger::CoreLogger->SetInfo("Engine Desturctor Called");
	}

	void Engine::run()
	{
		while (!m_Window.WindowShouldClose())
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			Event();

			Update();

			Render();

			m_Window.SwapBuffers();
			glfwPollEvents();
		}
	}


};