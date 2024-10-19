#pragma once

#include "../Core/Core.h"
#include "../Debug/Log.h"
#include "../3rdparty/glfw/include/GLFW/glfw3.h"

#include "Keyboard.h"
#include  "Mouse.h"

namespace TrexEngine
{

	class Input
	{
	public:
		TX_API static void PollEvents();

	public:
		TX_API static Keyboard keyboard;
		TX_API static Mouse    mouse;
	};

};