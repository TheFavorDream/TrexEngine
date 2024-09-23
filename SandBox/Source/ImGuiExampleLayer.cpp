#include "ImGuiExampleLayer.h"

ImGuiExampleLayer::ImGuiExampleLayer(ExampleLayer** p_ExampleLayer)
	: Layer("ImGuiExample"), Log("ImGuiExample"), m_ExampleLayer(p_ExampleLayer)
{

}

ImGuiExampleLayer::~ImGuiExampleLayer()
{

}

void ImGuiExampleLayer::OnAttach(TrexEngine::Window* p_Window)
{

	m_Window = p_Window;

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

	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
}

void ImGuiExampleLayer::OnDettach()
{

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	Log.Shutdown();
}

void ImGuiExampleLayer::OnEvent()
{

}

void ImGuiExampleLayer::EnableLayer()
{
	Enable = true;
	Log.SetWarning(LayerName + " got enabled");
}

void ImGuiExampleLayer::DisableLayer()
{
	Enable = false;
	Log.SetWarning(LayerName + " got disabled");
}


void ImGuiExampleLayer::OnRender()
{
	

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(m_Window->GetW(), m_Window->GetH());



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

			ImGui::SliderFloat("Transparensy", &i, 0.0f, 256.0f);
			ImGui::SliderFloat("Red", &R, 0.0f, 256.0f);
			ImGui::SliderFloat("Green", &G, 0.0f, 256.0f);
			ImGui::SliderFloat("Blue", &B, 0.0f, 256.0f);

			if (ImGui::Button("Invert"))
			{
				ScaleX *= -1;
				ScaleY *= -1;
			}

			ImGui::SameLine();
			ImGui::Checkbox("Sync", &Sync);
			ImGui::End();
		}

		ImGui::Begin("Layer Stack");

		ImGui::Checkbox("Enable Example Layer", &EnableExLayer);

		ImGui::End();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{

			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(m_Window->GetWindow());
		}

}

void ImGuiExampleLayer::OnUpdate(TrexEngine::Shader* P_Shader)
{

	if (EnableExLayer)
		(*m_ExampleLayer)->EnableLayer();
	else 
		(*m_ExampleLayer)->DisableLayer();

	P_Shader->SetUniformF("ScaleX", ScaleX);
	P_Shader->SetUniformF("ScaleY", ScaleY);

	P_Shader->SetUniformF("u_A", i / 256.0);
	P_Shader->SetUniformF("u_R", R / 256.0);
	P_Shader->SetUniformF("u_G", G / 256.0);
	P_Shader->SetUniformF("u_B", B/256.0);
}
