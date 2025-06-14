#pragma once


#include "../3rdparty/ImGui/Include/imgui.h"
#include "../3rdparty/ImGui/Include/imgui_impl_opengl3.h"
#include "../3rdparty/ImGui/Include/imgui_impl_glfw.h"
#include "../3rdparty/ImGui/Include/imgui_internal.h"


#include "../Core/Core.h"
#include "../Debug/Log.h"
#include "Widget.h"
#include "../Window/Window.h"
#include <unordered_map>


namespace TrexEngine
{
	class TrexUI
	{
	public:

		TX_API  TrexUI(Window* pWindow);
		TX_API ~TrexUI();
	
		TX_API int Init(Window* pWindow);
		TX_API int Shutdown();


		TX_API uint32 CreateWidget(std::string pTitle, ImVec2 pSize = ImVec2(400.0f, 400.0f), ImVec2 pPosition = ImVec2(0.0f, 0.0f), ImGuiWindowFlags pFlags = 0);
		TX_API int RemoveWidget(uint32 pID);

		TX_API Widget* GetWidget(uint32 ID);
		TX_API bool DoesWidgetExist(uint32 ID);

		TX_API void Render();

	private:
		void WidgetValidation(uint32 pID);

	private:
		std::unordered_map<uint32, Widget*> m_Widgets;

		ImGuiIO* m_IO=NULL;
		const char* m_GLSLVersion = "#version 330";
		bool m_CustomizedStyle = false;
	};
};