#include "UI.h"


namespace TrexEngine
{
	TrexUI::TrexUI()
	{
		Logger::CoreLogger->SetInfo("TrexUI Constructed");
	}

	TrexUI::~TrexUI()
	{
		Shutdown();
	}

	int TrexUI::Setup()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		m_IO = &ImGui::GetIO();
		m_IO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(TrexEngine::Engine::Get()->WindowManager->GetWindow(), true);
		ImGui_ImplOpenGL3_Init(m_GLSLVersion);

		ImGuiStyle& Style = ImGui::GetStyle();
		//Style.WindowRounding = 10.0f;
		Style.FrameRounding = 5.0f; 
		Style.ChildRounding = 5.0f;
		Style.ScrollbarRounding = 3.0f;

		return 0;
	}

	int TrexUI::Shutdown()
	{
		return 0;
	}

	void TrexUI::UpdateUI()
	{
		//UI needs the window's current size. so we retrive it every frame if it changes
		int W, H;
		TrexEngine::Engine::Get()->WindowManager->GetWindowSize(W, H);
		WindowSize = ImVec2(float(W), float(H));

	}

	void TrexUI::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void TrexUI::RenderUI()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void TrexUI::StartStaticWindow(std::string Title, ImVec4 SizeRatio)
	{
		ImGuiWindowFlags Flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;

		float w, h, x, y;
		w = WindowSize.x * SizeRatio.z/100.0f;
		h = WindowSize.y * SizeRatio.w/100.0f;
		x = WindowSize.x * SizeRatio.x/100.0f;
		y = WindowSize.y * SizeRatio.y/100.0f;

		ImGui::SetNextWindowSize(ImVec2(w,h));
		ImGui::SetNextWindowPos(ImVec2(x,y));

		ImGui::Begin(Title.c_str(), NULL, Flags);
	}

	void TrexUI::EndWindow()
	{
		ImGui::End();
	}



	bool TrexUI::Button(std::string Label, float W, float H)
	{
		bool State = ImGui::Button(Label.c_str(), ImVec2(W, H));
		return State;
	}

};
