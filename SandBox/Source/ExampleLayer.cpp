#include ".\Include\ExampleLayer.h"

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), Log("ExampleLayer")
{

}


void ExampleLayer::OnAttach(TrexEngine::Window* p_Window, TrexEngine::Shader* p_Shader, TrexEngine::Input* p_Events)
{
	m_Window = p_Window;
	m_Shader = p_Shader;
	m_Events = p_Events;

	VBL.push<float>(2);

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

void ExampleLayer::OnUpdate()
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