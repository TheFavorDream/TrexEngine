#pragma once

#include "../Core/Core.h"
#include "Element.h"

namespace TrexEngine
{
	class Text : public Element
	{
	public:

		TX_API  Text(const std::string& pText, ImVec2 pPosiotn);
		TX_API ~Text();
	
		TX_API void Render() override;
		
	};
};