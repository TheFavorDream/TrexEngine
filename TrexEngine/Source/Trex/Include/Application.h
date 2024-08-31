#pragma once
#include "Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/WindowManager.h"

namespace TrexEngine
{

	class TX_API Engine
	{
	public:

		//Constructor:
		Engine(const char* p_Title, int p_Width, int p_Height);

		//Distructor
		virtual ~Engine();

		//game loop
		void run();

		//should overload in client application:
		virtual void Render() = 0;
		virtual void Event() = 0;
		virtual void Update() = 0;

	protected:
		WindowManager m_Window;
		Renderer m_Renderer;
	};



	Engine* CreateApplication();

};