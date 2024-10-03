#include "Application.h"
#include "Log.h"

namespace TrexEngine
{

	Engine::Engine(const char* p_Title, int p_Width, int p_Height):
		m_Log("Core"), m_Window(new Window), m_Shader(new Shader)
	{

		m_Window->Init(p_Title, p_Width, p_Height);
		
		Renderer::GetInstance()->Init();

		m_Shader->CreateShaderProgram(VertexShaderSource, FragmentShaderSource);
		m_Shader->Bind();

		Keyboard::SetKeyCallBack(m_Window->GetWindow());
	}

	Engine::~Engine()
	{
		delete m_Shader;
		delete Renderer::s_RenderInstance;
		delete m_Window;

		m_Log.Shutdown();
	}

	void Engine::run()
	{
		while (!m_Window->WindowShouldClose())
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			for (auto &i : Layers)
			{
				if (!i->GetEnableState())
					continue;
				
				i->OnUpdate();
				i->OnRender();
			}

			m_Window->SwapBuffers();
			Input::PollEvents();
		}
	}

};