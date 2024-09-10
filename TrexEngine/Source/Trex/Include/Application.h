#pragma once
#include "Log.h"
#include "Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/WindowManager.h"
#include "Timer.h"

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

		//should override in client application:
		TX_API virtual void Render() = 0;
		TX_API virtual void Event() = 0;
		TX_API virtual void Update() = 0;

	private:
		Logger   m_Log;
	protected:
		WindowManager m_Window;
		Renderer m_Renderer;
		Shader m_Shader;
		Timer timer;


	};



	Engine* CreateApplication();

};