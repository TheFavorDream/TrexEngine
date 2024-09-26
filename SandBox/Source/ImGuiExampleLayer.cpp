#include "./Include/ImGuiExampleLayer.h"

ImGuiExample::ImGuiExample() : ImGuiLayer("ImGuiExampleLayer")
{

}

ImGuiExample::~ImGuiExample()
{


}

void ImGuiExample::OnAttach(TrexEngine::Window * p_Window, TrexEngine::Shader* p_Shader)
{

	Log.SetInfo("OnAttach Called. Init the Layer");

	if (p_Window != NULL && p_Shader != NULL)
	{
		m_Window = p_Window;
		m_Shader = p_Shader;
	}
	//Init the ImGui
	InitImGui();
}

void ImGuiExample::OnEvent()
{
}

void ImGuiExample::OnUpdate()
{
}

void ImGuiExample::OnRender()
{
	StartNewFrame();

	ImGuiBegin("Hello, World");

	ImGuiText("This is some Text");
	ImGuiText("This is some Text");
	ImGuiText("This is some Text");

	ImGuiText("This is some Text");

	ImGuiText("This is some Text");
	ImGuiText("This is some Text");
	ImGuiText("This is some Text");
	ImGuiText("This is some Text");
	ImGuiText("This is some Text");
	ImGuiText("This is some Text");
	ImGuiText("This is some Text");



	ImGuiEnd();

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

