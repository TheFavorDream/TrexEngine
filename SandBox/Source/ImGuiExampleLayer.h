#pragma once

#include "ExampleLayer.h"
#include "Trex.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"

class ImGuiExampleLayer : public TrexEngine::Layer
{

public:

	ImGuiExampleLayer(ExampleLayer** p_ExampleLayer);

	~ImGuiExampleLayer();


	void OnAttach(TrexEngine::Window* p_Window) override;
	void OnDettach() override;

	void OnRender() override;
	void OnUpdate(TrexEngine::Shader* P_Shader)	  override;
	void OnEvent()    override;

	void EnableLayer() override;
	void DisableLayer() override;

private:

	TrexEngine::Logger Log;
	ExampleLayer** m_ExampleLayer = NULL;

	bool EnableExLayer = true;

	float ScaleX = 1.0f;
	float ScaleY = 1.0f;
	float i = 255.0f;

	float R = 256.0f;
	float G = 256.0f;
	float B = 256.0f;
};