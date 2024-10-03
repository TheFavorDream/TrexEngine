#pragma once

#include "Layer.h"
#include "../Window/Window.h"

#include "../3rdparty/ImGui/Include/imgui_impl_glfw.h"
#include "../3rdparty/ImGui/Include/imgui_impl_opengl3.h"
#include "../3rdparty/ImGui/Include/imgui.h"

namespace TrexEngine
{
	class ImGuiLayer : public Layer
	{
	public:

		TX_API ImGuiLayer(std::string LayerName);
		TX_API ~ImGuiLayer();

		//ImGui Configure
		TX_API int InitImGui();
		TX_API int ShutdownImGui();

		
		TX_API void ImGuiEnableMultiViewports();
		TX_API void ImGuiDisableMultiViewports();

		TX_API void ImGuiSetDarkStyle();
		TX_API void ImGuiSetLightStyle();
		TX_API void ImGuiSetClassicStyle();


		//ImGui Wedget methods:
		TX_API void StartNewFrame();
		TX_API void EndNewFrame();

		TX_API bool ImGuiBegin(std::string p_Name);
		TX_API void ImGuiEnd();

		TX_API bool ImGuiBeginMenuBar();
		TX_API void ImGuiEndMenuBar();

		TX_API bool ImGuiBeginMenu(std::string p_Name);
		TX_API void ImGuiEndMenu();

		TX_API bool ImGuiMenuItem(std::string p_Name);


		TX_API void ImGuiSameLine();

		TX_API void ImGuiText(std::string p_Text);
		TX_API void ImGuiSliderFloat(std::string p_Label, float* p_Float, float p_Start, float p_End);
		TX_API void ImGuiSliderInt(std::string p_Label, int* p_Int, int p_Start, int p_End);

		TX_API bool ImGuiCheckBox(std::string p_Label, bool* p_Bool);
		TX_API bool ImGuiPushButton(std::string p_Label);





	protected:
		Logger Log;
		ImGuiConfigFlags NoDocking_Config;
		ImGuiConfigFlags NoViewports_Config;

	};
};