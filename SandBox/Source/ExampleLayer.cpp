#include "ExampleLayer.h"
ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), Log("ExampleLayer")
{

}

void ExampleLayer::OnAttach(TrexEngine::Window* p_Window)
{
	m_Window = p_Window;

	VBL.push<float>(2);
	//VBL.push<float>(3);

	VBO.BufferData(Vertices, sizeof(Vertices));

	VAO.AddLayouts(VBO, VBL);

	EBO.BufferData(Indicies, 6);

}

void ExampleLayer::OnEvent()
{
}


void ExampleLayer::OnRender()
{
	TrexEngine::Renderer::GetInstance()->DrawElements(VBO, EBO, VAO);
}

void ExampleLayer::OnUpdate(TrexEngine::Shader * p_Shader)
{

}


void ExampleLayer::OnDettach()
{

	Log.SetInfo("ExampleLayer Ondettach called");
	Log.Shutdown();
}

void ExampleLayer::EnableLayer()
{
	Enable = true;
	Log.SetWarning(LayerName + " got enabled");
}

void ExampleLayer::DisableLayer()
{
	Enable = false;
	Log.SetWarning(LayerName + " got disabled");

}




ExampleLayer::~ExampleLayer()
{

}