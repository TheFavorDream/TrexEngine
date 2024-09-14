
#include <iostream>
#include "ExampleLayer.h"
#include "Source/EntryPoint.h"

class Application : public TrexEngine::Engine
{
public:
	Application(const char* p_Title, int p_Width, int p_Height)
		: Engine(p_Title, p_Width, p_Height),
		ApplicationLogger("SandBox")
	{
		ApplicationLogger.SetInfo("SandBox Constructor Called");

		Layers.PushLayer(new ExampleLayer);
	}




	~Application() 
	{
		ApplicationLogger.SetInfo("SandBox Destructor called");
		Layers.PopLayer();
	}


private:
	TrexEngine::Logger ApplicationLogger;

};



TrexEngine::Engine* TrexEngine::CreateApplication()
{
	return new Application("SandBox", 1000, 500);
}