
#include <iostream>

#include "ExampleLayer.h"
#include "ImGuiExampleLayer.h"

#include "EntryPoint.h"

class Application : public TrexEngine::Engine
{
public:
	Application(const char* p_Title, int p_Width, int p_Height)
		: Engine(p_Title, p_Width, p_Height),
		ApplicationLogger("SandBox"),
		m_ExampleLayer(new ExampleLayer()),
		m_ImguiExampleLayer(new ImGuiExampleLayer(&m_ExampleLayer))
	{
		ApplicationLogger.SetInfo("SandBox Constructor Called");

		PushOverLayer(m_ImguiExampleLayer);
		PushLayer(m_ExampleLayer);

		ApplicationLogger.SetInfo("This is some Text");
		
	}


	~Application() 
	{
		delete m_ExampleLayer;
		delete m_ImguiExampleLayer;

		ApplicationLogger.SetInfo("SandBox Destructor called");
		ApplicationLogger.Shutdown();
	}


private:
	TrexEngine::Logger ApplicationLogger;

	ExampleLayer *m_ExampleLayer = NULL;
	ImGuiExampleLayer* m_ImguiExampleLayer = NULL;
};



TrexEngine::Engine* TrexEngine::CreateApplication()
{
	return new Application("SandBox", 1200, 600);
}