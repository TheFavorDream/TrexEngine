#pragma once

#include "Trex.h"


class UI : public TrexEngine::Layer, public TrexEngine::TrexUI
{
public:
	
	UI();
	~UI();

	void OnAttach() override;
	void OnEvent() override;
	void OnRender() override;
	void OnUpdate() override;
	void OnDettach() override;

private:
	TrexEngine::Logger Log;
	TrexEngine::Engine* Engine_Ref = NULL;
	ImVec4 ViewportRatio;
};