#include "Application.h"
#include "Log.h"

namespace TrexEngine
{

	Engine::Engine(const char* p_Title, int p_Width, int p_Height):
		m_Log("Core"), Shader()
	{

		//Init the Logging unit
		m_Log.SetInfo("Engine Constructor Called");


		Renderer.InitGLFW();

		Window.InitWindow(p_Title, p_Width, p_Height);
	
		Renderer.InitGLEW();

		Shader.CreateShaderProgram(VertexShaderSource, FragmentShaderSource);
		Shader.Bind();

	}

	Engine::~Engine()
	{
		Logger::CoreLogger->SetInfo("Engine Desturctor Called");
	}

	void Engine::run()
	{
		while (!Window.WindowShouldClose())
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			for (auto& i : Layers)
			{
				i->OnUpdate(Shader);
				i->OnRender(Renderer);
			}

			Window.SwapBuffers();
			glfwPollEvents();
		}
	}


};