#include "./Include/ImGuiExampleLayer.h"

ImGuiExample::ImGuiExample() : ImGuiLayer("ImGuiExampleLayer")
{

}

ImGuiExample::~ImGuiExample()
{


}


void ImGuiExample::RenderMenuBarItems()
{
	if (ImGuiBeginMenuBar())
	{

		if (ImGuiBeginMenu("File"))
		{

			if (ImGuiMenuItem("Window"))
			{
				RenderWindowWidget = !RenderWindowWidget;
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

			if (ImGuiMenuItem("Resources"))
			{
				RenderResourceWidget = !RenderResourceWidget;
			}

			if (ImGuiMenuItem("Shaders"))
			{
				RenderShaderWedget = !RenderShaderWedget;
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

void ImGuiExample::RenderWindowControlWidget()
{
	ImGuiBegin("Window Control");

	ImGuiText("Background Color:");
	
	ImGuiSliderFloat("Red", &WBG_R, 0.0f, 255.0f);
	ImGuiSliderFloat("Green", &WBG_G, 0.0f, 255.0f);
	ImGuiSliderFloat("Blue", &WBG_B, 0.0f, 255.0f);

	m_Window->SetWindowBackground(WBG_R/255.0f, WBG_G / 255.0f, WBG_B / 255.0f, 1.0f);

	ImGuiEnd();
}

void ImGuiExample::RenderShaderControlWidget()
{
	ImGuiBegin("Shader Control");

	const std::vector<std::string>& List = m_ShadersMG->GetShaderList();
	
	for (auto &i : List)
	{
		TrexEngine::Shader* Current = m_ShadersMG->GetShader(i);

		ImGuiText(i);
		ImGuiSameLine();
		if (ImGuiPushButton(("Use " + i)))
		{
			m_ShadersMG->BindShader(i);
			
		}
		ImGuiSameLine();
		if (ImGuiPushButton(("Reload " + i)))
		{
			Current->ReloadShader();
		}
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

void ImGuiExample::ResourceControlWidget()
{

	ImGuiBegin("Resource Table");

	ImGuiText("Current Resources:");

	auto Table = m_Textures->GetTextureTable();

	for (auto &i : Table)
	{
		ImGuiText(i.first);
		ImGuiSameLine();
		if (ImGuiPushButton("Load"))
		{
			m_Textures->GetTexture(i.first)->LoadTexture();
		}
		ImGuiSameLine();

		if (ImGuiPushButton("Free"))
		{
			m_Textures->GetTexture(i.first)->FreeTexture();
		}
	}

	ImGuiEnd();
}

void ImGuiExample::OnAttach(TrexEngine::Window * p_Window, TrexEngine::ShaderManager* p_ShadersMG, TrexEngine::Input* p_Events, TrexEngine::TextureManager* p_Textures)
{
	m_Events = p_Events;
	m_Textures = p_Textures;
	m_ShadersMG = p_ShadersMG;

	Log.SetInfo("OnAttach Called. Init the Layer");

	if (p_Window != NULL)
	{
		m_Window = p_Window;

	}
	//Init the ImGui
	InitImGui();
}

void ImGuiExample::OnEvent()
{


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

	if (m_Events->keyboard.IsKeyPressed(KEY_R))
	{
		RenderResourceWidget = !RenderResourceWidget;
	}
}

void ImGuiExample::OnUpdate()
{



}

void ImGuiExample::OnRender()
{
	StartNewFrame();

	if (RenderMenuBar)
		RenderMenuBarItems();

	if (RenderImGuiSettingWidget)
		RenderImGuiSettingsWidget();
	if (RenderMouse)
		RenderMouseWiget();
	if (RenderResourceWidget)
		ResourceControlWidget();
	if (RenderWindowWidget)
		RenderWindowControlWidget();
	if (RenderShaderWedget)
		RenderShaderControlWidget();

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

