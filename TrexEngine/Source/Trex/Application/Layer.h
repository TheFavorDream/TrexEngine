#pragma once

#include "../Core/Core.h"
#include "../Core/TextureManager.h"
#include "../Window/Window.h"
#include "../Platform/OpenGL/Shader.h"
#include "../Events/Input.h"
#include "../Core/ShaderManager.h"
#include <string>

namespace TrexEngine
{

	class Layer
	{
	public:
		TX_API Layer(std::string p_LayerName);
		TX_API virtual ~Layer();

		TX_API virtual void OnAttach (Window* p_Window, ShaderManager* p_ShadersMG, Input* p_Events, TextureManager* p_Textures)  = 0;
		TX_API virtual void OnDettach()  = 0;
		TX_API virtual void OnUpdate ()  = 0;
		TX_API virtual void OnRender ()  = 0;
		TX_API virtual void OnEvent  () = 0;

		TX_API virtual void EnableLayer() = 0;
		TX_API virtual void DisableLayer() = 0;

		TX_API inline bool GetEnableState() const { return Enable; }

		TX_API inline std::string& GetLayerName() { return LayerName; }
	protected:

		Window* m_Window;
		Input*  m_Events;
		TextureManager* m_Textures;
		ShaderManager*  m_ShadersMG;

		//For Debugging
		std::string LayerName;
		bool Enable = true;
	};

};