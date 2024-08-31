
#include <iostream>
#include "Source/Trex.h"

class Application : public TrexEngine::Engine
{
public:
	Application(const char* p_Title, int p_Width, int p_Height)
		: Engine(p_Title, p_Width, p_Height)
	{

	}

	void Event() override
	{

	}

	void Update() override
	{

	}

	void Render() override
	{

	}


	~Application() 
	{
		m_Renderer.Shutdown();
		m_Window.Shutdonw();
	}
};



TrexEngine::Engine* TrexEngine::CreateApplication()
{
	return new Application("SandBox", 1000, 500);
}