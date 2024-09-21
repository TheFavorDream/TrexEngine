#pragma once

#include "Core.h"
#include "Renderer/Window.h"
#include "Renderer/OpenGL/Shader.h"
#include <string>

namespace TrexEngine
{

	class Layer
	{
	public:
		TX_API Layer(std::string p_LayerName);
		TX_API virtual ~Layer();

		TX_API virtual void OnAttach (Window* p_Window)  = 0;
		TX_API virtual void OnDettach()  = 0;
		TX_API virtual void OnUpdate (Shader* P_Shader)  = 0;
		TX_API virtual void OnRender ()  = 0;
		TX_API virtual void OnEvent  ()  = 0;

	protected:

		//For Debugging
		std::string LayerName;
		Window* m_Window;
	};

};