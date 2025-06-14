#pragma once

#include "Trex.h"


class UI : public TrexEngine::Layer
{
public:
	
	UI();
	~UI();

	void OnAttach() override;
	void OnEvent() override;
	void OnRender() override;
	void OnUpdate() override;
	void OnDettach() override;


	void UpdateViewportRatio();
	void UpdateWidgetSize();

private:
	uint32 m_Control  = 0;
	uint32 m_Explorer = 0;
	
	uint32 m_Text = 0;
	uint32 m_Button = 0;
	uint32 m_Checkbox = 0;
	uint32 m_Slider = 0;

	TrexEngine::Logger Log;
	TrexEngine::TrexUI* Ui = NULL;
	ImVec4 ViewportRatio;
};