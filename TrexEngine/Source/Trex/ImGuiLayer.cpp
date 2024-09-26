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
		Log.SetInfo("Init the ImGui");
		glfwInit();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls     
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		// Setup Dear ImGui style
		ImGui::StyleColorsLight();
		ImGui::StyleColorsDark();


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

	TX_API void ImGuiLayer::ImGuiBegin(std::string p_Name)
	{
		ImGui::Begin(p_Name.c_str());
	}

	TX_API void ImGuiLayer::ImGuiText(std::string p_Text)
	{
		ImGui::Text(p_Text.c_str());
	}

	TX_API void ImGuiLayer::ImGuiEnd()
	{
		ImGui::End();
	}


};