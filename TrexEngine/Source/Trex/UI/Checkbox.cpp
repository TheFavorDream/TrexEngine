#include "Checkbox.h"

TrexEngine::Checkbox::Checkbox(std::string pTitle, ImVec2 pPosition, bool pState)
{
	m_Name = pTitle;
	m_Position = pPosition;
	m_State = pState;
}



TX_API void TrexEngine::Checkbox::Render()
{
	ImGui::SetCursorPos(m_Position);
	ImGui::Checkbox(m_Name.c_str(), &m_State);
}

