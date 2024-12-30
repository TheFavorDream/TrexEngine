#include ".\Include\ExampleLayer.h"

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), Log("ExampleLayer")
{

}


void ExampleLayer::OnAttach(TrexEngine::Window* p_Window, TrexEngine::ShaderManager* p_ShadersMG, TrexEngine::Input* p_Events, TrexEngine::ResourceManager* p_Resources)
{
	m_Window = p_Window;
	m_Events = p_Events;
	m_Resources = p_Resources;
	m_ShadersMG = p_ShadersMG;

	VBL.push<float>(2);
	VBL.push<float>(3);


	VBO.BufferData(Vertices, sizeof(Vertices));

	VAO.AddLayouts(VBO, VBL);

	EBO.BufferData(Indicies, sizeof(Indicies)/sizeof(unsigned int));
}


void ExampleLayer::OnEvent()
{
	

	if (m_Events->mouse.IsRightClickPressed())
	{
		Log.SetInfo("Right Click was pressed");
	}



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