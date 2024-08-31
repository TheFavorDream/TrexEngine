#pragma once
#include "Core.h"

namespace TrexEngine
{

	class TX_API Engine
	{
	public:
		Engine();

		virtual ~Engine();

		void run();

	private:

	};



	Engine* CreateApplication();

};