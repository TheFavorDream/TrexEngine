#include "Application.h"
#include "Log.h"

namespace TrexEngine
{

	Engine::Engine(const char* p_Title, int p_Width, int p_Height):
		m_Log("Core"), Renderer(Renderer::GetInstance()), Window(WindowManager::GetInstance()), Shader(Shader::GetInstance())
	{

		Renderer->InitGLFW();

		Window->InitWindow(p_Title, p_Width, p_Height);
	
		Renderer->InitGLEW();

		Shader->CreateShaderProgram(VertexShaderSource, FragmentShaderSource);
		Shader->Bind();
	}

	Engine::~Engine()
	{

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