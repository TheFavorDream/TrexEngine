#pragma once


#include "../Core/Core.h"
#include "../3rdparty/ImGui/Include/imgui.h"
#include <string>

namespace TrexEngine
{

	class Element
	{
	public:

		TX_API Element() = default;
		TX_API virtual ~Element() = default;
		
		TX_API virtual void Render() = 0;
		TX_API virtual void Ignore(bool ignore);
		
		TX_API inline ImVec2 GetPosition() { return m_Position; }
		TX_API inline ImVec2 GetSize() { return m_Size; }

		TX_API void SetName(std::string pName);
		TX_API inline const std::string& GetName() { return m_Name; }


	protected:
		std::string m_Name;

		ImVec2 m_Position;
		ImVec2 m_Size;
		bool   m_Enable;
	};

};