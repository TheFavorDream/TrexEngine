
#include <iostream>

#include ".\Include\ExampleLayer.h"
#include ".\Include\ImGuiExampleLayer.h"

#include "EntryPoint.h"



class Application : public TrexEngine::Engine
{
public:
	Application(const char* p_Title, int p_Width, int p_Height)
		: 
		Engine(p_Title, p_Width, p_Height),
		ApplicationLogger("SandBox"),
		m_ExampleLayer(new ExampleLayer()),
		m_ImGuiExample(new ImGuiExample())
	{
#ifdef RELEASE
		ApplicationLogger.SetLogLevel(TX_L0);
#endif
		ApplicationLogger.SetInfo("SandBox Constructor Called");

		WindowManager->SetWindowBackground(0.1f, 0.1f, 0.1f);

		std::string Path = "../../../Sandbox/Shaders/";
		if (IsDebuggerPresent())
		{
			Path = "./Shaders/";
		}

		ShadersManager->AddShader("Main", new TrexEngine::Shader(Path+"Def.glsl"));
		ShadersManager->AddShader("Skybox", new TrexEngine::Shader(Path+"Skybox.glsl"));
		ShadersManager->AddShader("Light", new TrexEngine::Shader(Path+"Light.glsl"));

		ShadersManager->BindShader("Main");

		PushLayer(m_ExampleLayer);
		PushOverLayer(m_ImGuiExample);

		LockFPS(true, 30);

		WindowManager->SetViewportRatio(30.0f, 30.0f, 70.0f, 70.0f);

	}

	~Application() 
	{

		PopLayer();
		PopOverLayer();

		delete m_ExampleLayer;
		delete m_ImGuiExample;
		
		ApplicationLogger.SetInfo("SandBox Destructor called");
		ApplicationLogger.Shutdown();
	}


private:
	TrexEngine::Logger ApplicationLogger;

	ExampleLayer *m_ExampleLayer = NULL;
	ImGuiExample *m_ImGuiExample = NULL;
};



TrexEngine::Engine* TrexEngine::CreateApplication()
{
	return new Application("TrexEngine SandBox", 1200, 600);
}