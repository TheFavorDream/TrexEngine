#pragma once
#include "Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/WindowManager.h"
#include "Log.h"

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

		//should overload in client application:
		TX_API virtual void Render() = 0;
		TX_API virtual void Event() = 0;
		TX_API virtual void Update() = 0;

	protected:
		WindowManager m_Window;
		Renderer m_Renderer;
	private:
		Logger   m_Log;
	};



	Engine* CreateApplication();

};