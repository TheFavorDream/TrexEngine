
#include <iostream>
#include "Source/Trex.h"

class Application : public TrexEngine::Engine
{
public:
	Application()
	{

	}

	~Application() 
	{

	}
};



TrexEngine::Engine* TrexEngine::CreateApplication()
{
	return new Application();
}