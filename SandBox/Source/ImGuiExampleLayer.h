#pragma once

#include "Trex.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"

class ImGuiExampleLayer : public TrexEngine::Layer
{

public:

	ImGuiExampleLayer();

	~ImGuiExampleLayer();


	void OnAttach() override;
	void OnDettach() override;

	void OnRender() override;
	void OnUpdate()	  override;
	void OnEvent()    override;

private:
	bool show_demo_window = true;
	bool show_another_window = true;

	float f = 1.0f;
	float i = 1.0f;
};