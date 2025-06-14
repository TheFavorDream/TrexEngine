#include "Text.h"


namespace TrexEngine
{

	Text::Text(const std::string& pText, ImVec2 pPosiotn)
	{
		m_Name = pText;
		m_Position = pPosiotn;
	}

	Text::~Text()
	{
	}

	void Text::Render()
	{
		ImGui::SetCursorPos(m_Position);
		ImGui::Text(m_Name.c_str());
	}
}