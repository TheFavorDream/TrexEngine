#pragma once

#include "Element.h"
#include "../3rdparty/ImGui/Include/imgui.h"
#include <string>

namespace TrexEngine
{
	class Button : public Element
	{
	public:

		TX_API  Button(std::string pName, ImVec2 pPosition, ImVec2 pSize = ImVec2(70.0f, 25.0f));
		TX_API ~Button();

		TX_API void Render() override;
		TX_API void Ignore(bool ignore) override;

		TX_API inline bool GetState() { return m_State; };

	private:

		bool m_State = false;
	};
};
