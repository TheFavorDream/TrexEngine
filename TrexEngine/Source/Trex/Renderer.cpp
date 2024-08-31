#include "Include/Renderer/Renderer.h"

namespace TrexEngine
{

	int Renderer::Init()
	{
		if (!glfwInit())
		{
			//TODO: Log the error messages
			return 1;
		}


		return 0;
	}


	int Renderer::Shutdown()
	{
		glfwTerminate();
		return 0;
	}

	Renderer::~Renderer()
	{
		Shutdown();
	}

};