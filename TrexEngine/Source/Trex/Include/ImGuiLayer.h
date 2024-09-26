#pragma once

#include "Layer.h"
#include "Renderer/Window.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"

namespace TrexEngine
{
	class ImGuiLayer : public Layer
	{
	public:

		TX_API ImGuiLayer(std::string LayerName);
		TX_API ~ImGuiLayer();


		TX_API void StartNewFrame();
		TX_API void EndNewFrame();

		TX_API void ImGuiBegin(std::string p_Name);
		TX_API void ImGuiText(std::string p_Text);
		TX_API void ImGuiEnd();


		TX_API int InitImGui();
		TX_API int ShutdownImGui();


	protected:
		Logger Log;
	};
};