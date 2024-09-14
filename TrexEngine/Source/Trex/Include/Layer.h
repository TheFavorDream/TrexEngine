#pragma once

#include "Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/OpenGL/Shader.h"
#include <string>

namespace TrexEngine
{

	class TX_API Layer
	{
	public:
		Layer(std::string p_LayerName);
		virtual ~Layer();

		virtual void OnAttach ()  = 0;
		virtual void OnDettach()  = 0;
		virtual void OnUpdate (const Shader&  shader)  = 0;
		virtual void OnRender (const Renderer& Render)  = 0;
		virtual void OnEvent  ()  = 0;

	private:

		//For Debugging
		std::string LayerName;
	};

};