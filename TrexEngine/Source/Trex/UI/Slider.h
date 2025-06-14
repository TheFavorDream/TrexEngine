#pragma once

#include "../Core/Core.h"
#include "Element.h"

namespace TrexEngine
{

	enum SliderType { INT, FLOAT, DOUBLE };

	class SliderFloat : public Element
	{
	public:
		TX_API SliderFloat(std::string pLabel, ImVec2 pPosition, float pDefData=0.0f, float pMin=0.0f, float pMax=10.0f);

		TX_API void Render() override;


		TX_API void SetData(float pData);
		TX_API void SetMin (float pMin) ;
		TX_API void SetMax (float pMax) ;
		
		TX_API inline float GetData() { return m_Data; }
		TX_API inline float GetMin() { return m_Min; }
		TX_API inline float GetMax() { return m_Max; }

	private:
		float m_Data = 0.0f;
		float m_Min = 0.0f;
		float m_Max = 0.0f;

	};
};