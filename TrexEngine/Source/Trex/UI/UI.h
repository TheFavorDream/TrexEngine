#pragma once


#include "../3rdparty/ImGui/Include/imgui.h"
#include "../3rdparty/ImGui/Include/imgui_impl_opengl3.h"
#include "../3rdparty/ImGui/Include/imgui_impl_glfw.h"
#include "../3rdparty/ImGui/Include/imgui_internal.h"

#include "../Core/Core.h"
#include "../Debug/Log.h"
#include "../Application/Application.h"

namespace TrexEngine
{
	class TrexUI
	{
	public:

		TX_API TrexUI();
		TX_API ~TrexUI();

		TX_API int Setup();
		TX_API int Shutdown();

		TX_API void UpdateUI();

		TX_API void NewFrame();
		TX_API void RenderUI();

		TX_API void StartStaticWindow(std::string Title, ImVec4 SizeRatio);
		TX_API void EndWindow();

		TX_API bool Button(std::string Label,float W=0.0f, float H=0.0f);
	private:
		ImGuiIO* m_IO=NULL;
		ImVec2 WindowSize;
		const char* m_GLSLVersion = "#version 330";
		bool m_CustomizedStyle = false;
	};
};