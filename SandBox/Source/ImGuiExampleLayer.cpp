#include "ImGuiExampleLayer.h"

ImGuiExampleLayer::ImGuiExampleLayer()
	: Layer("ImGuiExample"), Log("ImGuiExample")
{

}

ImGuiExampleLayer::~ImGuiExampleLayer()
{

}


void ImGuiExampleLayer::OnAttach()
{
	glfwInit();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls     
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();


	// Setup Platform/Renderer backends
	GLFWwindow* window = TrexEngine::WindowManager::GetInstance()->GetWindow();
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void ImGuiExampleLayer::OnDettach()
{

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiExampleLayer::OnEvent()
{

}

void ImGuiExampleLayer::OnRender()
{
	

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(TrexEngine::WindowManager::GetInstance()->GetW(), TrexEngine::WindowManager::GetInstance()->GetH());



		static bool Sync = false;


		{

			ImGui::Begin("Shape Settings");
			ImGui::Text("ImGui On TrexEngine");

			ImGui::SliderFloat("Y", &ScaleY, -1.0f, 1.0f);
			ImGui::SameLine();
			ImGui::InputFloat("ScaleY", &ScaleY);
			if (Sync)
				ScaleX = ScaleY;

			ImGui::SliderFloat("X", &ScaleX, -1.0f, 1.0f);
			ImGui::SameLine();
			ImGui::InputFloat("ScaleX", &ScaleX);
			if (Sync)
				ScaleY = ScaleX;
			ImGui::SliderFloat("Transparensy", &i, 0.0f, 2.0f);

			if (ImGui::Button("Invert"))
			{
				ScaleX *= -1;
				ScaleY *= -1;
			}

			ImGui::SameLine();
			ImGui::Checkbox("Sync", &Sync);
			ImGui::End();
		}


		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* current_context = TrexEngine::WindowManager::GetInstance()->GetWindow();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(current_context);
		}

}

void ImGuiExampleLayer::OnUpdate()
{
	TrexEngine::Shader::GetInstance()->SetUniformF("ScaleX", ScaleX);
	TrexEngine::Shader::GetInstance()->SetUniformF("ScaleY", ScaleY);
	TrexEngine::Shader::GetInstance()->SetUniformF("u_Color", i);
}
