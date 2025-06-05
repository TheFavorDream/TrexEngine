#include "Include/SandboxUI.h"

UI::UI()
	: Layer("UI"), Log("UI")
{
	Engine_Ref = TrexEngine::Engine::Get();
}

UI::~UI()
{
}

void UI::OnAttach()
{
	Log.SetInfo("Initializing");
	Setup();
}

void UI::OnEvent()
{
}

void UI::OnRender()
{
	NewFrame();

	StartStaticWindow("##General", ImVec4(0.0f, 0.0f, (100.0f-ViewportRatio.z), 100.0f));


	if (Button("Some Button"))
	{
		Log.SetInfo("Button Pressed");
	}

	if (Button("Some Button 2"))
	{
		Log.SetInfo("Button2 Pressed");
	}


	EndWindow();


	StartStaticWindow("##Status", ImVec4((100.0f - ViewportRatio.z), ViewportRatio.w, ViewportRatio.z, (100.0f-ViewportRatio.w)));
	EndWindow();

	RenderUI();
}

void UI::OnUpdate()
{
	UpdateUI();
	
	float x, y, w, h;
	Engine_Ref->WindowManager->GetViewportRatio(x,y,w,h);
	ViewportRatio = ImVec4(x,y,w,h);
}

void UI::OnDettach()
{
	Shutdown();
	Log.SetInfo("Shuting down");
	Log.Shutdown();
}

