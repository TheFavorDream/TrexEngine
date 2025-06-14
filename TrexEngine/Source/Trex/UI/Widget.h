#pragma once

#include "../Core/Core.h"
#include "../3rdparty/ImGui/Include/imgui.h"
#include "../Core/Timer.h"
#include "../Debug/Log.h"

#include "Element.h"
#include "Button.h"
#include "Checkbox.h"
#include "Text.h"
#include "Slider.h"

#include <vector>
#include <string>
#include <unordered_map>

namespace TrexEngine
{
	class Widget
	{
	public:
		 TX_API  Widget(uint32 pID, std::string pTitle, ImVec2 pSize= ImVec2(400.0f,400.0f), ImVec2 pPosition = ImVec2(0.0f, 0.0f), ImGuiWindowFlags pFlags=0);
		 TX_API ~Widget();

		 TX_API void Update();
		 TX_API void Render();

		 TX_API void SetSize(uint32 W, uint32 H);
		 TX_API void SetPosition(uint32 X, uint32 Y);

		 TX_API uint32 NewButton(std::string pName, uint32 X, uint32 Y, uint32 W = 70, uint32 H = 25);
		 TX_API uint32 NewCheckBox(std::string pTitle, uint32 X, uint32 Y);
		 TX_API uint32 NewText(std::string pText, uint32 X, uint32 Y);
		 TX_API uint32 NewSliderFloat(std::string pName, uint32 X, uint32 Y, float pDefData = 0.0f, float pMin = 0.0f, float pMax = 10.0f);

		 TX_API Button*   GetButton(const uint32 pID);
		 TX_API Checkbox* GetCheckbox(const uint32 pID);
		 TX_API Text*     GetText(const uint32 pID);
		 TX_API SliderFloat* GetSliderF(const uint32 pID);

		 TX_API inline uint32 GetID() { return m_ID; }

		 TX_API inline bool IsOpen() { return m_Open; }
		 TX_API void Ignore(bool pIgnore);

	private:

		void ElementValidation(uint32 pID);

	private:

		std::unordered_map<uint32, Element*> m_Elements;

		uint32 m_ID = 0;
		ImGuiWindowFlags m_Flags;
		std::string m_Title;
		ImVec2 m_Size;
		ImVec2 m_Position;
		bool m_Open = true;
	};
};