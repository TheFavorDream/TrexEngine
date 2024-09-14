#pragma once

#include "Trex/Include/Application.h"


extern TrexEngine::Engine* TrexEngine::CreateApplication();

#ifdef PLATFORM_WINDOWS

int main(int argc, char** arvg)
{
	TrexEngine::Engine* app = TrexEngine::CreateApplication();
	app->run();
	delete app;
	return 0;
}

#endif