#include "./Include/ImGuiExampleLayer.h"

ImGuiExample::ImGuiExample() : ImGuiLayer("ImGuiExampleLayer")
{
#ifdef RELEASE
	Log.SetLogLevel(TX_L0);
#endif
	m_Engine = TrexEngine::Engine::Get();
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

			if (ImGuiMenuItem("Log"))
			{
				RenderLogControl = !RenderLogControl;
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

	m_Engine->WindowManager->SetWindowBackground(WBG_R / 255.0f, WBG_G / 255.0f, WBG_B / 255.0f, 1.0f);

	ImGuiText("DeltaTime (ms):" + std::to_string(TrexEngine::Timer::GetDeltaTime()));

	ImGuiEnd();
}

void ImGuiExample::RenderShaderControlWidget()
{
	ImGuiBegin("Shader Control");

	const std::vector<std::string>& List = m_Engine->ShadersManager->GetShaderList();

	for (auto &i : List)
	{
		TrexEngine::Shader* Current = m_Engine->ShadersManager->GetShader(i);

		ImGuiText(i);
		ImGuiSameLine();
		if (ImGuiPushButton(("Use " + i)))
		{
			m_Engine->ShadersManager->BindShader(i);

		}
		ImGuiSameLine();
		if (ImGuiPushButton(("Reload " + i)))
		{
			Current->ReloadShader();
		}
	}

	ImGuiEnd();
}

void ImGuiExample::RenderLogControlWidget()
{
	ImGuiBegin("Log");

	static int CurrentLogger = -1;

	for (int i = 0; i < TrexEngine::Logger::s_Loggers.size(); i++)
	{
		ImGuiSameLine();
		if (ImGuiPushButton(TrexEngine::Logger::s_Loggers[i]->GetProfileName()))
		{
			CurrentLogger = i;
		}
	}

	ImGuiNextLine();

	int Level = 1;
	for (int i = 0; i < 3; i++)
	{
		ImGuiSameLine();
		if (ImGuiPushButton("Level:"+std::to_string(i+1)))
		{
			Level = i + 1;
		}
	}


	if (CurrentLogger < 0)
	{
		ImGuiEnd();
		return;
	}

	if (ImGuiPushButton("Clear"))
	{
		TrexEngine::Logger::s_Loggers[CurrentLogger]->ResetLogs();
	}

	ImGuiNextLine();
	ImGuiText("Current Profile:");
	ImGuiSameLine();
	ImGuiText(TrexEngine::Logger::s_Loggers[CurrentLogger]->GetProfileName());




	std::vector<TrexEngine::LogEvent> Logs = TrexEngine::Logger::s_Loggers[CurrentLogger]->GetLogs();

	for (auto &i : Logs)
	{
		ImGuiText(i.m_Description);
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

	ImGuiText("Mouse Position (via CallBack): " + std::to_string(m_Engine->events.mouse.GetMouseX()) + "X, " + std::to_string(m_Engine->events.mouse.GetMouseY()) + "Y.");
	double x, y;
	TrexEngine::Input::mouse.GetCursorPosition(m_Engine->WindowManager->GetWindow(), &x, &y);
	ImGuiText("Mouse Position (via direct):" + std::to_string(x) + "X, " + std::to_string(y) + "Y");


	std::string State = TrexEngine::Input::mouse.IsLeftClickPressed() ? "Pressed" : "Released";
	ImGuiText("Mouse Left State:" + State);

	State = TrexEngine::Input::mouse.IsRightClickPressed() ? "Pressed" : "Released";
	ImGuiText("Mouse Right State:" + State);

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

	auto Table = m_Engine->TexturesManager->GetTextureTable();

	for (auto &i : Table)
	{
		ImGuiText(i.first);
		ImGuiSameLine();
		if (ImGuiPushButton("Load " + i.first))
		{
			m_Engine->TexturesManager->GetTexture(i.first)->LoadTexture();
		}
		ImGuiSameLine();

		if (ImGuiPushButton("Free " + i.first))
		{
			m_Engine->TexturesManager->GetTexture(i.first)->FreeTexture();
		}
	}

	ImGuiEnd();
}

void ImGuiExample::OnAttach()
{

	Log.SetInfo("OnAttach Called. Init the Layer");

	//Init the ImGui
	InitImGui();

	TrexEngine::vec4 Color = m_Engine->WindowManager->GetBackground();
	WBG_R = Color.x * 255.0f;
	WBG_G = Color.y * 255.0f;
	WBG_B = Color.z * 255.0f;
}

void ImGuiExample::OnEvent()
{


	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_E))
	{
		RenderMenuBar = true;
	}

	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_ESCAPE))
	{
		RenderMenuBar = false;
	}


	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_P))
	{
		m_Engine->events.keyboard.StartTextInput(Text);
	}

	if (m_Engine->events.keyboard.IsInputingText())
	{
		if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_ENTER))
		{
			m_Engine->events.keyboard.StopTextInput();
		}
	}

	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_T))
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
	if (RenderLogControl)
		RenderLogControlWidget();
	if (m_Engine->events.keyboard.IsInputingText())
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

