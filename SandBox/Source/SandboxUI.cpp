#include "Include/SandboxUI.h"

UI::UI()
	: Layer("UI"), Log("UI")
{
	Ui = TrexEngine::Engine::Get()->UICore;
}

UI::~UI()
{
}

void UI::OnAttach()
{
	Log.SetInfo("Initializing");



	m_Control  = Ui->CreateWidget("Control");
	m_Explorer = Ui->CreateWidget("Explorer");

	UpdateViewportRatio();
	UpdateWidgetSize();

	m_Text =     Ui->GetWidget(m_Control)->NewText("This is some useful text", 10, 30);
	m_Button =   Ui->GetWidget(m_Control)->NewButton("Press Me", 10, 50);
	m_Checkbox = Ui->GetWidget(m_Control)->NewCheckBox("Checkbox", 10, 80);
	m_Slider = Ui->GetWidget(m_Control)->NewSliderFloat("Slider", 10, 110);
}

void UI::OnEvent()
{
	if (TrexEngine::Input::keyboard.IsKeyPressed(TX_KEY_R) == true)
	{
		Ui->GetWidget(m_Explorer)->Ignore(true);
	}

	if (TrexEngine::Input::keyboard.IsKeyPressed(TX_KEY_E) == true)
	{
		Ui->GetWidget(m_Explorer)->Ignore(false);
	}
}

void UI::OnRender()
{
	Ui->Render();
	UpdateWidgetSize();
}

void UI::OnUpdate()
{


	if (!Ui->DoesWidgetExist(m_Explorer))
		return;

	if (Ui->GetWidget(m_Control)->GetCheckbox(m_Checkbox)->GetState())
	{
		Ui->GetWidget(m_Control)->GetText(m_Text)->SetName("Checked!");
	}

	if (!Ui->GetWidget(m_Control)->GetCheckbox(m_Checkbox)->GetState())
	{
		Ui->GetWidget(m_Control)->GetText(m_Text)->SetName("Not Checked!");

	}

	UpdateViewportRatio();
}

void UI::OnDettach()
{

	Log.SetInfo("Shuting down");
	Log.Shutdown();
}

void UI::UpdateViewportRatio()
{
	float x, y, w, h;
	TrexEngine::Engine::Get()->WindowManager->GetViewportRatio(x, y, w, h);
	ViewportRatio = ImVec4(x, y, w, h);
}

void UI::UpdateWidgetSize()
{
	int WindowWidth = TrexEngine::Engine::Get()->WindowManager->GetW();
	int WindowHeight = TrexEngine::Engine::Get()->WindowManager->GetH();

	ImVec2 ControlSize = ImVec2(((100.0f - ViewportRatio.z) / 100.0f)*WindowWidth, WindowHeight);
	ImVec2 ExplorerSize = ImVec2((ViewportRatio.z / 100.0f*WindowWidth), (100.0f - ViewportRatio.w) / 100.0f*WindowHeight);
	ImVec2 ExplorerPos = ImVec2((ViewportRatio.x / 100.0f*WindowWidth), ViewportRatio.w / 100.0f*WindowHeight);

	if (!Ui->DoesWidgetExist(m_Explorer))
		return;
	Ui->GetWidget(m_Control)->SetSize(ControlSize.x, ControlSize.y);
	Ui->GetWidget(m_Explorer)->SetPosition(ExplorerPos.x, ExplorerPos.y);
	Ui->GetWidget(m_Explorer)->SetSize(ExplorerSize.x, ExplorerSize.y);
}

