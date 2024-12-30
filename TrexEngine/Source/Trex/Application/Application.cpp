#include "Application.h"
#include "Log.h"

namespace TrexEngine
{


	Engine::Engine(const char* p_Title, int p_Width, int p_Height):
		m_Log("Core"), WindowManager(new Window), ShadersManager(new ShaderManager)
	{

		WindowManager->CreateNewWindow(p_Title, p_Width, p_Height);
		
		Renderer::GetInstance()->Init();

		events.keyboard.SetKeyCallBack(WindowManager->GetWindow());
		events.mouse.SetMouseCallBacks(WindowManager->GetWindow());
	}

	Engine::~Engine()
	{
		delete ShadersManager;
		delete Renderer::s_RenderInstance;
		delete WindowManager;

		m_Log.Shutdown();
	}

	void Engine::run()
	{
		while (!WindowManager->WindowShouldClose())
		{
			GLCall(glClearColor(WindowManager->GetBackground().x, WindowManager->GetBackground().y, WindowManager->GetBackground().z, WindowManager->GetBackground().a));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			for (int i = Layers.GetLayersNumber()-1; i >= 0; --i)
			{
				if (!Layers.GetLayer(i)->GetEnableState())
					continue;
				Layers.GetLayer(i)->OnEvent();
			}

			for (auto &i : Layers)
			{
				if (!i->GetEnableState())
					continue;
				
				i->OnUpdate();
				i->OnRender();
			}

			WindowManager->SwapBuffers();
			Input::PollEvents();
		}
	}

};