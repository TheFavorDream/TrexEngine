
#include <iostream>
#include "Source/Trex.h"

class Application : public TrexEngine::Engine
{
public:
	Application(const char* p_Title, int p_Width, int p_Height)
		: Engine(p_Title, p_Width, p_Height), ApplicationLogger("SandBox")
	{
		ApplicationLogger.SetInfo("SandBox Constructor Called");
		Test = new TrexEngine::Logger("Test");

		Test->SetInfo("Im Working");
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
		delete Test;

	}


private:
	TrexEngine::Logger ApplicationLogger;
	TrexEngine::Logger* Test = NULL;
};



TrexEngine::Engine* TrexEngine::CreateApplication()
{
	return new Application("SandBox", 1000, 500);
}