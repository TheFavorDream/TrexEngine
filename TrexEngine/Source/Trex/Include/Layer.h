#pragma once

#include "Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/OpenGL/Shader.h"
#include <string>

namespace TrexEngine
{

	class  Layer
	{
	public:
		TX_API Layer(std::string p_LayerName);
		TX_API virtual ~Layer();

		TX_API virtual void OnAttach ()  = 0;
		TX_API virtual void OnDettach()  = 0;
		TX_API virtual void OnUpdate ()  = 0;
		TX_API virtual void OnRender ()  = 0;
		TX_API virtual void OnEvent  ()  = 0;

	protected:

		//For Debugging
		std::string LayerName;
	};

};