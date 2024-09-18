#include "ImGuiExampleLayer.h"

ImGuiExampleLayer::ImGuiExampleLayer()
	: Layer("ImGuiExample")
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
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

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

		static bool Sync = false;

		{

			ImGui::Begin("Shape Settings");                          
			ImGui::Text("ImGui On TrexEngine");               

			ImGui::SliderFloat("Scale", &f, 0.0f, 1.0f);      
			if (Sync)
				i = f;
			

			ImGui::SliderFloat("Transparensy", &i, 0.0f, 1.0f);          

			if (Sync)
				f = i;
			


			ImGui::Checkbox("Sync", &Sync);


			ImGui::Text("Average %.3f ms/frame(%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiExampleLayer::OnUpdate()
{
	TrexEngine::Shader::GetInstance()->SetUniformF("Scale", f);
	TrexEngine::Shader::GetInstance()->SetUniformF("u_Color", i);
}
