#include "Slider.h"


namespace TrexEngine
{
	SliderFloat::SliderFloat(std::string pLabel, ImVec2 pPosition, float pDefData, float pMin, float pMax)
		: m_Data(pDefData), m_Max(pMax), m_Min(pMin)
	{
		m_Position = pPosition;
		m_Name = pLabel;
	}

	void SliderFloat::Render()
	{
		ImGui::SetCursorPos(m_Position);
		ImGui::SliderFloat(m_Name.c_str(), &m_Data, m_Min, m_Max);
	}

	void SliderFloat::SetData(float pData)
	{
		m_Data = pData;
	}

	void SliderFloat::SetMin(float pMin)
	{
		m_Min = pMin;
	}

	void SliderFloat::SetMax(float pMax)
	{
		m_Max = pMax;
	}

}
