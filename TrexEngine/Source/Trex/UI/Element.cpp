#include "Element.h"

namespace TrexEngine
{
	void Element::Ignore(bool ignore)
	{
		m_Enable = !ignore;
	}

	void Element::SetName(std::string pName)
	{
		m_Name = pName;
	}
}
