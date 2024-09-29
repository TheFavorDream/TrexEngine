#pragma once

#include "Trex.h"

class ImGuiExample : public TrexEngine::ImGuiLayer
{
public:

	ImGuiExample();

	~ImGuiExample();


	void RenderUniformSettingWidget();
	void RenderMenuBarItems();
	void RenderImGuiSettingsWidget();

	void OnAttach(TrexEngine::Window* p_Window, TrexEngine::Shader* p_Shader) override;
	void OnEvent()      override;
	void OnUpdate()     override;
	void OnRender()     override;
	void OnDettach()    override;
	void EnableLayer()  override;
	void DisableLayer() override;

private:

	float R			   = 255.0f;
	float G            = 255.0f;
	float B			   = 255.0f;
	float Transparency = 255.0f;

	bool RenderUniformWidget      = false;
	bool RenderImGuiSettingWidget = false;

	bool Dark_Style = true;
	bool Prev_Dark_Style = Dark_Style;

	bool Enable_Docking = true;
	bool Prev_EnableState = Enable_Docking;

};