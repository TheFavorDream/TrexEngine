#include "./Include/ImGuiExampleLayer.h"

ImGuiExample::ImGuiExample() : ImGuiLayer("ImGuiExampleLayer")
{

}

ImGuiExample::~ImGuiExample()
{


}

void ImGuiExample::RenderUniformSettingWidget()
{

	ImGuiBegin("Shader Uniform Settings");

	if (ImGuiPushButton("Close"))
	{
		RenderUniformWidget = false;
	}

	if (ImGuiSliderFloat("Red", &R, 0.0f, 255.0f))     ShouldUpdate = true;
	if (ImGuiSliderFloat("Green", &G, 0.0f, 255.0f))   ShouldUpdate = true;
	if (ImGuiSliderFloat("Blue", &B, 0.0f, 255.0f))    ShouldUpdate = true;

	if (ImGuiSliderFloat("Scale X", &ScaleX, 0.0f, 1.0f)) ShouldUpdate = true;
	if (ImGuiSliderFloat("Scale Y", &ScaleY, 0.0f, 1.0f)) ShouldUpdate = true;


	ImGuiEnd();
}

void ImGuiExample::RenderMenuBarItems()
{
	if (ImGuiBeginMenuBar())
	{

		if (ImGuiBeginMenu("File"))
		{
			if (ImGuiMenuItem("Uniforms"))
			{
				RenderUniformWidget = !RenderUniformWidget;
			}

			if (ImGuiMenuItem("Settings"))
			{
				RenderImGuiSettingWidget = !RenderImGuiSettingWidget;
			}

			ImGuiEndMenu();
		}

		if (ImGuiBeginMenu("Tools"))
		{
			if (ImGuiMenuItem("Mouse"))
			{
				RenderMouse = !RenderMouse;
			}

			ImGuiEndMenu();
		}

		ImGuiEndMenuBar();
	}
}

void ImGuiExample::RenderImGuiSettingsWidget()
{
	ImGuiBegin("ImGui Settings");

	ImGuiCheckBox("Enable Multi View ports", &Enable_Docking);

	if (Prev_EnableState != Enable_Docking)
	{
		if (Enable_Docking)
			ImGuiEnableMultiViewports();
		else
			ImGuiDisableMultiViewports();
		Prev_EnableState = Enable_Docking;
	}

	ImGuiSameLine();
	ImGuiCheckBox("Dark Style", &Dark_Style);

	if (Prev_Dark_Style != Dark_Style)
	{
		if (Dark_Style)
			ImGuiSetDarkStyle();
		else
			ImGuiSetLightStyle();
		Prev_Dark_Style = Dark_Style;
	}
	ImGuiEnd();
}

void ImGuiExample::RenderTextBox()
{
	ImGuiBegin("Text Inputing");

	ImGuiText(Text);

	ImGuiEnd();
}

void ImGuiExample::RenderMouseWiget()
{
	ImGuiBegin("Mouse");

	ImGuiText("Mouse Position: " + std::to_string(m_Events->mouse.GetMouseX()) + "X, " + std::to_string(m_Events->mouse.GetMouseY()) + "Y.");

	if (ImGuiPushButton("Close"))
	{
		RenderMouse = false;
	}

	ImGuiEnd();
}

void ImGuiExample::OnAttach(TrexEngine::Window * p_Window, TrexEngine::Shader* p_Shader, TrexEngine::Input* p_Events)
{
	m_Events = p_Events;

	Log.SetInfo("OnAttach Called. Init the Layer");

	if (p_Window != NULL && p_Shader != NULL)
	{
		m_Window = p_Window;
		m_Shader = p_Shader;
	}
	//Init the ImGui
	InitImGui();
}

void ImGuiExample::OnEvent()
{
	if (m_Events->keyboard.IsKeyPressed(KEY_W))
	{
		RenderUniformWidget = !RenderUniformWidget;
	}

	if (m_Events->keyboard.IsKeyPressed(KEY_E))
	{
		RenderMenuBar = true;
	}

	if (m_Events->keyboard.IsKeyPressed(KEY_ESCAPE))
	{
		RenderMenuBar = false;
	}


	if (m_Events->keyboard.IsKeyPressed(KEY_S))
	{
		m_Events->keyboard.StartTextInput(Text);
	}

	if (m_Events->keyboard.IsInputingText())
	{
		if (m_Events->keyboard.IsKeyPressed(KEY_ENTER))
		{
			m_Events->keyboard.StopTextInput();
		}
	}
}

void ImGuiExample::OnUpdate()
{

	if (ShouldUpdate)
	{
		m_Shader->SetUniformF("u_R", R / 256.0f);
		m_Shader->SetUniformF("u_G", G / 256.0f);
		m_Shader->SetUniformF("u_B", B / 256.0f);
		m_Shader->SetUniformF("u_ScaleX", ScaleX);		m_Shader->SetUniformF("u_ScaleY", ScaleY);
		ShouldUpdate = false;
	}

}

void ImGuiExample::OnRender()
{
	StartNewFrame();

	if (RenderMenuBar)
		RenderMenuBarItems();

	if (RenderUniformWidget)
		RenderUniformSettingWidget();
	if (RenderImGuiSettingWidget)
		RenderImGuiSettingsWidget();
	if (RenderMouse)
		RenderMouseWiget();

	if (m_Events->keyboard.IsInputingText())
	{
		RenderTextBox();
	}

	EndNewFrame();
}

void ImGuiExample::OnDettach()
{
	Log.SetInfo("OnDettach Called. Shuting down the layer");
	ShutdownImGui();
}

void ImGuiExample::EnableLayer()
{
	Enable = true;
}

void ImGuiExample::DisableLayer()
{
	Enable = false;
}

