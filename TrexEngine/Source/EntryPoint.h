#pragma once

#include "./Trex/Application/Application.h"


extern TrexEngine::Engine* TrexEngine::CreateApplication();

#ifdef PLATFORM_WINDOWS
#include <windows.h>

int  main(int argc, char** arvg)
{
	TrexEngine::Engine* app = TrexEngine::CreateApplication();
	app->run();
	delete app;
	return 0;
}

#endif