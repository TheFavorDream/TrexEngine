#pragma once
#include "../Core.h"
#include "WindowManager.h"

namespace TrexEngine
{

	class TX_API Renderer
	{
	public:

		int Init();

		int Shutdown();

		~Renderer();

	public:
		bool IsInit = false;
	};

};