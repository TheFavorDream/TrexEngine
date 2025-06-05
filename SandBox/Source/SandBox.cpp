
#include <iostream>

#include ".\Include\Wednesdex.h"
#include ".\Include\SandboxUI.h"
#include "EntryPoint.h"



class Application : public TrexEngine::Engine
{
public:
	Application(const char* p_Title, int p_Width, int p_Height)
		:
		Engine(p_Title, p_Width, p_Height),
		m_Wednesdex(new Wednesdex()),
		m_UI(new UI())
	{

		WindowManager->SetWindowBackground(0.05f, 0.05f, 0.05f);

		std::string Path = "../../../Sandbox/Shaders/";
		if (IsDebuggerPresent())
		{
			Path = "./Shaders/";
		}

		ShadersManager->AddShader("Main", new TrexEngine::Shader(Path+"Def.glsl"));
		ShadersManager->AddShader("Skybox", new TrexEngine::Shader(Path+"Skybox.glsl"));
		ShadersManager->AddShader("Light", new TrexEngine::Shader(Path+"Light.glsl"));
		ShadersManager->AddShader("Sphere", new TrexEngine::Shader(Path + "Sphere.glsl"));


		PushLayer(m_Wednesdex);
		PushOverLayer(m_UI);

		LockFPS(false, 30);

		WindowManager->SetViewportRatio(20.0f, 20.0f, 80.0f, 80.0f);

	}

	~Application() 
	{

		PopLayer();
		PopOverLayer();

		delete m_Wednesdex;
		delete m_UI;


	}


private:

	Wednesdex *m_Wednesdex = NULL;
	UI* m_UI = NULL;
};



TrexEngine::Engine* TrexEngine::CreateApplication()
{
	return new Application("Wednesdex Simulator", 1200, 600);
}