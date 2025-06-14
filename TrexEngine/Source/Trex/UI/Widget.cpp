#include "Widget.h"

namespace TrexEngine
{
	Widget::Widget(uint32 pID, std::string pTitle, ImVec2 pSize, ImVec2 pPosition, ImGuiWindowFlags pFlags)
		:m_Title(pTitle), m_Size(pSize), m_Position(pPosition), m_Flags(pFlags)
	{
		m_ID = pID;
	}

	Widget::~Widget()
	{
		Logger::CoreLogger->SetInfo("Widget [" + std::to_string(m_ID) + "] Destructed");
	}
	
	void Widget::Update()
	{
	
	}
	
	void Widget::Render()
	{
		ImGui::SetNextWindowPos(m_Position);
		ImGui::SetNextWindowSize(m_Size);
		
		ImGui::Begin(m_Title.c_str(), &m_Open, m_Flags);
		

		for (auto &i : m_Elements)
		{
			i.second->Render();
		}

		ImGui::End();
	}
	
	void Widget::SetSize(uint32 W, uint32 H)
	{
		m_Size = ImVec2(W, H);
	}
	
	void Widget::SetPosition(uint32 X, uint32 Y)
	{
		m_Position = ImVec2(X, Y);
	}

	uint32 Widget::NewButton(std::string pName, uint32 X, uint32 Y, uint32 W, uint32 H)
	{
		uint32 ID = m_Elements.size();
		m_Elements[ID] = new Button(pName, ImVec2(X, Y), ImVec2(W, H));
		return ID;
	}

	uint32 Widget::NewText(std::string pText, uint32 X, uint32 Y)
	{
		uint32 ID = m_Elements.size();
		m_Elements[ID] = new Text(pText, ImVec2(X, Y));
		return ID;
	}

	TX_API uint32 Widget::NewSliderFloat(std::string pName, uint32 X, uint32 Y, float pDefData, float pMin, float pMax)
	{
		uint32 ID = m_Elements.size();
		m_Elements[ID] = new SliderFloat(pName, ImVec2(X, Y), pDefData, pMin, pMax);
		return ID;
	}



	uint32 Widget::NewCheckBox(std::string pTitle, uint32 X, uint32 Y)
	{
		uint32 ID = m_Elements.size();
		m_Elements[ID] = new Checkbox(pTitle, ImVec2(X, Y));
		return ID;
	}

	Button* Widget::GetButton(const uint32 pID)
	{
		ElementValidation(pID);
		return static_cast<Button*>(m_Elements[pID]);
	}
	
	Checkbox * Widget::GetCheckbox(const uint32 pID)
	{
		ElementValidation(pID);
		return static_cast<Checkbox*>(m_Elements[pID]);
	}

	TX_API Text * Widget::GetText(const uint32 pID)
	{
		ElementValidation(pID);
		return static_cast<Text*>(m_Elements[pID]);
	}

	TX_API SliderFloat * Widget::GetSliderF(const uint32 pID)
	{
		ElementValidation(pID);
		return static_cast<SliderFloat*>(m_Elements[pID]);
	}
	
	void Widget::Ignore(bool pIgnore)
	{
		m_Open = !pIgnore;
	}

	void Widget::ElementValidation(uint32 pID)
	{
		if (m_Elements.find(pID) == m_Elements.end())
		{
			Logger::CoreLogger->SetError("Invalid Element ID");
			STOP();
		}
	}
};