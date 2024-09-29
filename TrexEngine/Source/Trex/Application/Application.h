#pragma once
#include "../3rdparty/GL/glew.h"

#include "../Debug/Log.h"
#include "../Core/Core.h"
#include "../Renderer/Renderer.h"
#include "../Window/Window.h"
#include "../Core/Timer.h"
#include "../Core/LayerContainer.h"
#include "../Platform/OpenGL/Shader.h"
#include "../Application/ImGuiLayer.h"

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
			p_NewLayer->OnAttach(m_Window, m_Shader);
		}

		void PopLayer()
		{
			Layers.PopLayer();
		}

		void PushOverLayer(Layer* p_NewLayer)
		{
			Layers.PushOverLayer(p_NewLayer);
			p_NewLayer->OnAttach(m_Window, m_Shader);
		}

		void PopOverLayer()
		{
			Layers.PopOverLayer();
		}

	private:
		Logger   m_Log;

	protected:


		Window *m_Window   = NULL;
		Shader *m_Shader = NULL;
		Timer			timer;
		LayerContainer  Layers;

		Layer* m_ImGuiLayer = NULL;


	};



	Engine* CreateApplication();

};