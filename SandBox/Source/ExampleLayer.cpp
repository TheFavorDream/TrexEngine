#include ".\Include\ExampleLayer.h"

ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), Log("ExampleLayer"), TrexCamera({ 0.0f, 0.0f, 5.0f }, 45)
{

}


void ExampleLayer::OnAttach(TrexEngine::Window* p_Window, TrexEngine::ShaderManager* p_ShadersMG, TrexEngine::Input* p_Events, TrexEngine::TextureManager* p_Textures)
{
	m_Window = p_Window;
	m_Events = p_Events;
	m_Textures = p_Textures;
	m_ShadersMG = p_ShadersMG;


	VBO.UploadData(GL_FLOAT, 5, 36, GL_STATIC_DRAW, (void*)Vertex);
	VBO.Bind();

	VBL.push<float>(3);
	VBL.push<float>(2);

	//EBO.BufferData(Indicies, 6);

	VAO.AddLayouts(VBO, VBL);

	m_Textures->AddTexture("Wall", new Texture2D("G:\\Dev\\TrexEngine\\SandBox\\Resources\\wall.jpg"));

	m_ShadersMG->GetCurrentShader()->SetUniformI1("Tex", 0);
	m_Textures->GetTexture("Wall")->LoadTexture();
}


void ExampleLayer::OnEvent()
{
	
	CameraKeyControll();
	CameraMouseControll();
}

void ExampleLayer::OnUpdate()
{
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(float(Timer::GetCurrentElapsed()/10.0)), glm::vec3(0.0f, 1.0f, 1.0f));

	m_ShadersMG->GetCurrentShader()->SetUniformMat4("Model", (model));

}

void ExampleLayer::OnRender()
{
	TrexCamera.Matrix(0.1f, 100.f, m_Window->GetW(), m_Window->GetH(), m_ShadersMG->GetCurrentShader());
	m_Textures->BindTexture("Wall");
	TrexEngine::Renderer::GetInstance()->DrawArrays(VBO, VAO);
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

void ExampleLayer::CameraKeyControll()
{
	float Speed = 0.05f;
	if (m_Events->keyboard.GetKeyCurrentState(TX_KEY_W) == KEY_PRESS)
	{
		TrexCamera.GetCameraPosition() += Speed * TrexCamera.GetOriantation();
	}

	if (m_Events->keyboard.GetKeyCurrentState(TX_KEY_S) == KEY_PRESS)
	{
		TrexCamera.GetCameraPosition() -= Speed * TrexCamera.GetOriantation();
	}

	if (m_Events->keyboard.GetKeyCurrentState(TX_KEY_A) == KEY_PRESS)
	{
		TrexCamera.GetCameraPosition() += Speed * -glm::normalize(glm::cross(TrexCamera.GetOriantation(), TrexCamera.GetUP()));
	}

	if (m_Events->keyboard.GetKeyCurrentState(TX_KEY_D) == KEY_PRESS)
	{
		TrexCamera.GetCameraPosition() += Speed * glm::normalize(glm::cross(TrexCamera.GetOriantation(), TrexCamera.GetUP()));
	}

	if (m_Events->keyboard.GetKeyCurrentState(TX_KEY_SPACE) == KEY_PRESS)
	{
		TrexCamera.GetCameraPosition() += Speed * TrexCamera.GetUP();
	}

	if (m_Events->keyboard.GetKeyCurrentState(TX_KEY_LEFT_SHIFT) == KEY_PRESS)
	{
		TrexCamera.GetCameraPosition() += Speed * -TrexCamera.GetUP();
	}
}

void ExampleLayer::CameraMouseControll()
{

}


ExampleLayer::~ExampleLayer()
{
}