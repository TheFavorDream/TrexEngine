#include ".\Include\ExampleLayer.h"

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), Log("ExampleLayer")
{

}


void ExampleLayer::OnAttach(TrexEngine::Window* p_Window, TrexEngine::ShaderManager* p_ShadersMG, TrexEngine::Input* p_Events, TrexEngine::TextureManager* p_Textures)
{
	m_Window = p_Window;
	m_Events = p_Events;
	m_Textures = p_Textures;
	m_ShadersMG = p_ShadersMG;


	VBO.UploadData(GL_FLOAT, 7, 4, GL_STATIC_DRAW, (void*)Vertex);
	VBO.Bind();

	VBL.push<float>(2);
	VBL.push<float>(3);
	VBL.push<float>(2);

	VAO.AddLayouts(VBO, VBL);
	EBO.BufferData(Indicies, 6);

	m_Textures->AddTexture("Wall", new Texture2D("G:\\Dev\\TrexEngine\\SandBox\\Resources\\wall.jpg"));

	m_ShadersMG->GetCurrentShader()->SetUniformI1("Tex", 0);
	m_Textures->GetTexture("Wall")->LoadTexture();
}


void ExampleLayer::OnEvent()
{
	
		
}


void ExampleLayer::OnRender()
{

	m_Textures->BindTexture("Wall");
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