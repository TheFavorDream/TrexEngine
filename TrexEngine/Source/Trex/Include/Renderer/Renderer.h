#pragma once
#include "GL/glew.h"
#include "../Core.h"
#include "WindowManager.h"

namespace TrexEngine
{

	class  Renderer
	{
	public:

		TX_API int InitGLFW();

		TX_API int InitGLEW();

		TX_API int Shutdown();

		TX_API ~Renderer();

	public:
		bool IsInit = false;
	};

};