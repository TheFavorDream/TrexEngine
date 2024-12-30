#pragma once

#include "Trex.h"

class ImGuiExample : public TrexEngine::ImGuiLayer
{
public:

	ImGuiExample();

	~ImGuiExample();



	void RenderMenuBarItems();
	void RenderImGuiSettingsWidget();
	void RenderTextBox();
	void RenderMouseWiget();
	void ResourceControlWidget();
	void RenderWindowControlWidget();
	void RenderShaderControlWidget();

	void OnAttach(TrexEngine::Window* p_Window, TrexEngine::ShaderManager* p_ShadersMG, TrexEngine::Input* p_Events, TrexEngine::ResourceManager* p_Resources) override;
	void OnEvent()      override;
	void OnUpdate()     override;
	void OnRender()     override;
	void OnDettach()    override;
	void EnableLayer()  override;
	void DisableLayer() override;

private:

	std::string Text;

	float WBG_R = 0.0f;
	float WBG_G = 0.0f;
	float WBG_B = 0.0f;


	bool ShouldUpdate = false;

	bool RenderMouse = false;
	bool RenderImGuiSettingWidget = false;
	bool RenderMenuBar = true;
	bool RenderResourceWidget = false;
	bool RenderWindowWidget = false;
	bool RenderShaderWedget = false;

	bool Dark_Style = true;
	bool Prev_Dark_Style = Dark_Style;

	bool Enable_Docking = true;
	bool Prev_EnableState = Enable_Docking;

};