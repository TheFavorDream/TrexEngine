
#include <iostream>

#include ".\Include\ExampleLayer.h"
#include ".\Include\ImGuiExampleLayer.h"

#include "EntryPoint.h"

class Application : public TrexEngine::Engine
{
public:
	Application(const char* p_Title, int p_Width, int p_Height)
		: Engine(p_Title, p_Width, p_Height),
		ApplicationLogger("SandBox"),
		m_ExampleLayer(new ExampleLayer()),
		m_ImGuiExample(new ImGuiExample())
	{
		ApplicationLogger.SetInfo("SandBox Constructor Called");

		PushLayer(m_ExampleLayer);
		PushOverLayer(m_ImGuiExample);
		
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