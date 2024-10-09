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
	if (m_Events->keyboard.GetKeyState(KEY_R) == TrexEngine::PRESS)
	{
		m_Shader->SetUniformF("u_R", 1.0f);
		m_Shader->SetUniformF("u_B", 0.0f);
		m_Shader->SetUniformF("u_G", 0.0f);
	}

	if (m_Events->keyboard.GetKeyState(KEY_G) == TrexEngine::PRESS)
	{
		m_Shader->SetUniformF("u_R", 0.0f);
		m_Shader->SetUniformF("u_B", 0.0f);
		m_Shader->SetUniformF("u_G", 1.0f);
	}

	if (m_Events->keyboard.GetKeyState(KEY_B) == TrexEngine::PRESS)
	{
		m_Shader->SetUniformF("u_R", 0.0f);
		m_Shader->SetUniformF("u_B", 1.0f);
		m_Shader->SetUniformF("u_G", 0.0f);
	}

	if (m_Events->keyboard.GetKeyState(KEY_T) == TrexEngine::PRESS)
	{
		m_Shader->SetUniformF("u_A", 1.0f);
	}
	if (m_Events->keyboard.GetKeyState(KEY_Y) == TrexEngine::PRESS)
	{
		m_Shader->SetUniformF("u_A", 0.0f);
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