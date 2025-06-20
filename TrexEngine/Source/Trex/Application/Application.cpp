
#include "Application.h"
#include "Log.h"

namespace TrexEngine
{

	Engine* Engine::s_Ref = NULL;

	Engine::Engine(const char* p_Title, int p_Width, int p_Height):
		m_Log("Core")
	{

#ifdef TX_RELEASE
		Logger::CoreLogger->SetLogLevel(TX_L0);
#endif
		Engine::s_Ref = this;

		WindowManager = new Window;
		ShadersManager = new ShaderManager;
		TexturesManager = new TextureManager;

		WindowManager->CreateNewWindow(p_Title, p_Width, p_Height);
		Renderer::GetInstance()->Init();

		events.keyboard.SetKeyCallBack(WindowManager->GetWindow());
		events.mouse.SetMouseCallBacks(WindowManager->GetWindow());
		m_IsRunning = true;
	
		UICore = new TrexUI(WindowManager);
	}

	Engine::~Engine()
	{
		delete UICore;
		delete TexturesManager;
		delete ShadersManager;
		delete Renderer::s_RenderInstance;
		delete WindowManager;

		m_Log.Shutdown();
	}

	void Engine::run()
	{
		while (m_IsRunning)
		{


			GLCall(glClearColor(WindowManager->GetBackground().x, WindowManager->GetBackground().y, WindowManager->GetBackground().z, WindowManager->GetBackground().a));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

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
			WindowManager->UpdateWindowSize();
			Input::PollEvents();


			m_IsRunning = !WindowManager->WindowShouldClose();

			std::this_thread::sleep_for(m_IsFPSLocked*(std::chrono::microseconds(1000 / m_LockedFPS-(int)Timer::GetDeltaTime())));
			Timer::DeltaTime(glfwGetTime());
		}
	}

	void Engine::LockFPS(bool Lock, int FPS)
	{
		m_IsFPSLocked = Lock;

		if (FPS != 0)
			m_LockedFPS = FPS;
	}

};