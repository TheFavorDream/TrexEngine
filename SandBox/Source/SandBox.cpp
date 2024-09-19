
#include <iostream>

#include "ExampleLayer.h"
#include "ImGuiExampleLayer.h"

#include "EntryPoint.h"

class Application : public TrexEngine::Engine
{
public:
	Application(const char* p_Title, int p_Width, int p_Height)
		: Engine(p_Title, p_Width, p_Height),
		ApplicationLogger("SandBox")
	{
		ApplicationLogger.SetInfo("SandBox Constructor Called");

		Layers.PushLayer(new ExampleLayer);
		Layers.PushLayer(new ImGuiExampleLayer);
	}




	~Application() 
	{
		ApplicationLogger.SetInfo("SandBox Destructor called");
	}


private:
	TrexEngine::Logger ApplicationLogger;

};



TrexEngine::Engine* TrexEngine::CreateApplication()
{
	return new Application("SandBox", 1200, 600);
}