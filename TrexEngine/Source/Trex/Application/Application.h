#pragma once
#include "../3rdparty/GL/glew.h"
#include <thread>
#include "../Debug/Log.h"
#include "../Core/Core.h"
#include "../Core/TextureManager.h"
#include "../Renderer/Renderer.h"
#include "../Window/Window.h"
#include "../Core/Timer.h"
#include "../Core/LayerContainer.h"
#include "../Platform/OpenGL/Shader.h"
#include "../UI/UI.h"
#include "../Events/Input.h"
#include "../Events/Keyboard.h"
#include "../Core/ShaderManager.h"

namespace TrexEngine
{

	class  Engine
	{
	public:

		//Constructor:
		TX_API Engine(const char* p_Title, int p_Width, int p_Height);

		//Distructor
		TX_API virtual ~Engine();

		//loop
		TX_API void run();

		void PushLayer(Layer* p_NewLayer)
		{
			Layers.PushLayer(p_NewLayer);
			p_NewLayer->OnAttach();
		}

		void PopLayer()
		{
			Layers.PopLayer();
		}

		void PushOverLayer(Layer* p_NewLayer)
		{
			Layers.PushOverLayer(p_NewLayer);
			p_NewLayer->OnAttach();
		}

		void PopOverLayer()
		{
			Layers.PopOverLayer();
		}


		TX_API inline static Engine* Get() { return s_Ref; }

		TX_API void LockFPS(bool Lock, int FPS=60);

		inline int GetFPS() { return m_LockedFPS; }
	private:
		Logger   m_Log;
		bool m_IsRunning = false;
		bool m_IsFPSLocked = false;
		int m_LockedFPS = 60; //Should not be zero

	public:

		Window*         WindowManager   = NULL;
		ShaderManager*  ShadersManager  = NULL;
		TextureManager* TexturesManager = NULL;
		TrexUI*         UICore = NULL;

		Input events;
		Timer			timer;
		LayerContainer  Layers;
		Layer* m_ImGuiLayer = NULL;
	private:
		static Engine* s_Ref;
	};



	Engine* CreateApplication();

};