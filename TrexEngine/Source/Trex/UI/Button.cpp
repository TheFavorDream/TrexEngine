#include "Button.h"

namespace TrexEngine
{
	Button::Button(std::string pName, ImVec2 pPosition, ImVec2 pSize)
	{
		m_Name = pName;
		m_Position = pPosition;
		m_Size = pSize;
	}

	Button::~Button()
	{
	}

	void Button::Render()
	{
		ImGui::SetCursorPos(m_Position);
		m_State = ImGui::Button(m_Name.c_str(), m_Size);
	}

	void Button::Ignore(bool ignore)
	{
		
	}

}
