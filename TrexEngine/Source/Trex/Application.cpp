#include "Application.h"
#include "Log.h"

namespace TrexEngine
{

	Engine::Engine(const char* p_Title, int p_Width, int p_Height):
		m_Log("Core")
	{

		//Init the Logging unit
		m_Log.SetInfo("Engine Constructor Called");


		Renderer::GetInstance()->InitGLFW();

		WindowManager::GetInstance()->InitWindow(p_Title, p_Width, p_Height);
	
		Renderer::GetInstance()->InitGLEW();

		Shader::GetInstance()->CreateShaderProgram(VertexShaderSource, FragmentShaderSource);
		Shader::GetInstance()->Bind();

	}

	Engine::~Engine()
	{
		Logger::CoreLogger->SetInfo("Engine Desturctor Called");

		delete Shader::shader;
		delete WindowManager::s_WindowManager;
		delete Renderer::Render;
	}

	void Engine::run()
	{
		while (!WindowManager::GetInstance()->WindowShouldClose())
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			for (auto& i : Layers)
			{
				i->OnUpdate();
				i->OnRender();
			}

			WindowManager::GetInstance()->SwapBuffers();
			glfwPollEvents();
		}
	}


};