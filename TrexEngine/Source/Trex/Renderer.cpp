#include "Include/Renderer/Renderer.h"
#include "Log.h"

namespace TrexEngine
{
	//extern TrexEngine::Logger TrexEngine::TrexLogger("Core");

	int Renderer::InitGLFW()
	{
		if (!glfwInit())
		{
			Logger::CoreLogger->SetError("Unable to Init GLFW");
			return 1;
		}
		return 0;
	}

	int Renderer::InitGLEW()
	{
		if (glewInit() != GLEW_OK)
		{
			Logger::CoreLogger->SetError("Unable to Init GLEW");
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