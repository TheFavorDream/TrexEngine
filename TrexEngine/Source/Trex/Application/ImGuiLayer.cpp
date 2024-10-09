#include "ImGuiLayer.h"


namespace TrexEngine
{
	ImGuiLayer::ImGuiLayer(std::string LayerName) : Layer(LayerName), Log(LayerName)
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	int ImGuiLayer::InitImGui()
	{

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls     
		NoDocking_Config = io.ConfigFlags;
		NoViewports_Config = io.ConfigFlags;

		ImGuiEnableMultiViewports();

		// Setup Dear ImGui style
		
		ImGuiSetDarkStyle();

		// Setup Platform/Renderer backends

		ImGui_ImplOpenGL3_Init("#version 330");


		ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
		return 0;
	}

	int ImGuiLayer::ShutdownImGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		Log.SetWarning("ImGui got Destroyed");
		return 0;
	}
	

	TX_API void ImGuiLayer::ImGuiEnableMultiViewports()
	{
		Log.SetInfo("MutlView Ports got Enabled");
		ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_ViewportsEnable;
	}

	TX_API void ImGuiLayer::ImGuiDisableMultiViewports()
	{
		Log.SetInfo("MutlView Ports got Disabled");
		ImGui::GetIO().ConfigFlags = NoViewports_Config;

	}

	TX_API void ImGuiLayer::ImGuiSetDarkStyle()
	{
		ImGui::StyleColorsDark();
	}

	TX_API void ImGuiLayer::ImGuiSetLightStyle()
	{
		ImGui::StyleColorsLight();
	}

	TX_API void ImGuiLayer::ImGuiSetClassicStyle()
	{
		TX_API void ImGuiSetLightStyle();
	}

	void ImGuiLayer::StartNewFrame()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::EndNewFrame()
	{
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{

			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(m_Window->GetWindow());
		}
	}

	TX_API bool ImGuiLayer::ImGuiBegin(std::string p_Name)
	{
		return ImGui::Begin(p_Name.c_str());
	}

	TX_API void ImGuiLayer::ImGuiText(std::string p_Text)
	{
		ImGui::Text(p_Text.c_str());
	}

	TX_API bool ImGuiLayer::ImGuiBeginMenuBar()
	{
		return ImGui::BeginMainMenuBar();
	}

	TX_API void ImGuiLayer::ImGuiEndMenuBar()
	{
		ImGui::EndMainMenuBar();
	}

	TX_API bool ImGuiLayer::ImGuiBeginMenu(std::string p_Name)
	{
		return ImGui::BeginMenu(p_Name.c_str());
	}

	TX_API void ImGuiLayer::ImGuiEndMenu()
	{
		ImGui::EndMenu();
	}

	TX_API bool ImGuiLayer::ImGuiMenuItem(std::string p_Name)
	{
		return ImGui::MenuItem(p_Name.c_str());
	}

	TX_API void ImGuiLayer::ImGuiSameLine()
	{
		ImGui::SameLine();
	}

	TX_API bool ImGuiLayer::ImGuiSliderFloat(std::string p_Label, float * p_Float, float p_Start, float p_End)
	{
		return ImGui::SliderFloat(p_Label.c_str(), p_Float, p_Start, p_End);
	}

	TX_API void ImGuiLayer::ImGuiSliderInt(std::string p_Label, int * p_Int, int p_Start, int p_End)
	{
		ImGui::SliderInt(p_Label.c_str(), p_Int, p_Start, p_End);
	}

	TX_API bool ImGuiLayer::ImGuiCheckBox(std::string p_Label, bool * p_Bool)
	{
		ImGui::Checkbox(p_Label.c_str(), p_Bool);
		return *p_Bool;
	}

	TX_API bool ImGuiLayer::ImGuiPushButton(std::string p_Label)
	{
		return ImGui::Button(p_Label.c_str());
	}

	TX_API void ImGuiLayer::ImGuiEnd()
	{
		ImGui::End();
	}


};