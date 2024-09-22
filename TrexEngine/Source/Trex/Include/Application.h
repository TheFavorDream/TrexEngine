#pragma once
#include "GL/glew.h"

#include "Log.h"
#include "Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Window.h"
#include "Timer.h"
#include "LayerContainer.h"
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

		void PushLayer(Layer* p_NewLayer)
		{
			Layers.PushLayer(p_NewLayer);
			p_NewLayer->OnAttach(m_Window);
		}

		void PushOverLayer(Layer* p_NewLayer)
		{
			Layers.PushOverLayer(p_NewLayer);
			p_NewLayer->OnAttach(m_Window);
		}

	private:
		Logger   m_Log;

	protected:


		Window *m_Window   = NULL;
		Shader *m_Shader = NULL;
		Timer			timer;
		LayerContainer  Layers;




	};



	Engine* CreateApplication();

};