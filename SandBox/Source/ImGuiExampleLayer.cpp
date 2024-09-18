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


		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)


			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiExampleLayer::OnUpdate()
{

}
