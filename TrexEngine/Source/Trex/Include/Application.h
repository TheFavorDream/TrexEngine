#pragma once
#include "Log.h"
#include "Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/WindowManager.h"
#include "Timer.h"
#include "LayerContainer.h"

#include "Renderer/OpenGL/VertexBuffer.h"
#include "Renderer/OpenGL/IndexBuffer.h"
#include "Renderer/OpenGL/VertexArray.h"
#include "Renderer/OpenGL/VertexBufferLayout.h"
#include "Renderer/OpenGL/Shader.h"

namespace TrexEngine
{

	class  Engine
	{
	public:

		//Constructor:
		TX_API Engine(const char* p_Title, int p_Width, int p_Height);

		//Distructor
		TX_API virtual ~Engine();

		//game loop
		TX_API void run();

	private:
		Logger   m_Log;
	protected:
		WindowManager	Window;
		Renderer		Renderer;
		Timer			timer;
		Shader			Shader;
		LayerContainer  Layers;

	};



	Engine* CreateApplication();

};