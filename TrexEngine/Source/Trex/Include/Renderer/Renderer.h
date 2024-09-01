#pragma once
#define GLEW_STATIC
#include "GL/glew.h"
#include "../Core.h"
#include "WindowManager.h"

namespace TrexEngine
{

	class TX_API Renderer
	{
	public:

		int InitGLFW();

		int InitGLEW();

		int Shutdown();

		~Renderer();

	public:
		bool IsInit = false;
	};

};