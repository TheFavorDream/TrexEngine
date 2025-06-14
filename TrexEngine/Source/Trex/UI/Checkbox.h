#pragma once


#include "../Core/Core.h"
#include "Element.h"

namespace TrexEngine
{
	class Checkbox : public Element
	{
	public:

		TX_API  Checkbox(std::string pTitle, ImVec2 pPosition, bool pState=false);
		TX_API void Render() override;

		TX_API inline bool GetState() { return m_State; };

	private:
		bool m_State;
	};
};