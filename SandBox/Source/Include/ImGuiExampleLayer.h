#pragma once

#include "Trex.h"

class ImGuiExample : public TrexEngine::ImGuiLayer
{
public:

	ImGuiExample();

	~ImGuiExample();


	void OnAttach(TrexEngine::Window* p_Window, TrexEngine::Shader* p_Shader) override;
	void OnEvent() override;
	void OnUpdate() override;
	void OnRender() override;
	void OnDettach() override;
	void EnableLayer() override;
	void DisableLayer() override;

private:

};