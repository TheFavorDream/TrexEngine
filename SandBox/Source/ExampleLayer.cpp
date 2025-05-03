#include ".\Include\ExampleLayer.h"
#include <filesystem>


ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), Log("ExampleLayer"), TrexCamera({ 0.0f, 0.0f, 5.0f }, 45)
{
#ifdef RELEASE
	Log.SetLogLevel(TX_L0);
#endif
}


void ExampleLayer::OnAttach(TrexEngine::Window* p_Window, TrexEngine::ShaderManager* p_ShadersMG, TrexEngine::Input* p_Events, TrexEngine::TextureManager* p_Textures)
{
	m_Window = p_Window;
	m_Events = p_Events;
	m_Textures = p_Textures;
	m_ShadersMG = p_ShadersMG;


	VBO.UploadData(GL_FLOAT, 5, 24, GL_STATIC_DRAW, (void*)Vertex);
	VBO.Bind();

	VBL.push<float>(3);
	VBL.push<float>(2);

	EBO.BufferData(Indicies, 36);

	VAO.AddLayouts(VBO, VBL);


	std::string T = "../../../Sandbox/Resources/";
	if (IsDebuggerPresent())
	{
		T = "./Resources/";
	}


	m_Textures->AddTexture("Wall", new Texture2D(T+"wall.jpg"));
	m_Textures->AddTexture("Container", new Texture2D(T + "container.jpg"));

	m_ShadersMG->GetCurrentShader()->SetUniformI1("Tex", 0);
	m_Textures->GetTexture("Wall")->LoadTexture();
	m_Textures->GetTexture("Container")->LoadTexture();

	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

}


void ExampleLayer::OnEvent()
{
	
	CameraKeyControll();
	CameraMouseControll();
}

void ExampleLayer::OnUpdate()
{
	//model = glm::mat4(1.0f);
	if (TrexEngine::Input::keyboard.IsKeyPressed(TX_KEY_LEFT))
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	if (TrexEngine::Input::keyboard.IsKeyPressed(TX_KEY_UP))
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	if (TrexEngine::Input::keyboard.IsKeyPressed(TX_KEY_RIGHT))
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));


	m_ShadersMG->GetCurrentShader()->SetUniformMat4("Model", (model));

}

void ExampleLayer::OnRender()
{
	for (int i = 0; i < 20; i++)
	{
		TrexCamera.Matrix(0.1f, 100.f, m_Window->GetW(), m_Window->GetH(), m_ShadersMG->GetCurrentShader(), Coords[i]);
		if (i%2==0)
			m_Textures->BindTexture("Wall");
		else
			m_Textures->BindTexture("Container");

		TrexEngine::Renderer::GetInstance()->DrawElements(VBO, EBO, VAO);
	}
	
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
	if (m_Events->keyboard.IsKeyPressed(TX_KEY_W))
	{
		TrexCamera.MoveFront();
	}

	if (m_Events->keyboard.IsKeyPressed(TX_KEY_S))
	{
		TrexCamera.MoveBack();
	}

	if (m_Events->keyboard.IsKeyPressed(TX_KEY_A))
	{
		TrexCamera.MoveLeft();
	}

	if (m_Events->keyboard.IsKeyPressed(TX_KEY_D))
	{
		TrexCamera.MoveRight();
	}

	if (m_Events->keyboard.IsKeyPressed(TX_KEY_SPACE))
	{
		TrexCamera.MoveUp();
	}

	if (m_Events->keyboard.IsKeyPressed(TX_KEY_LEFT_CONTROL))
	{
		TrexCamera.MoveDown();
	}
}

void ExampleLayer::CameraMouseControll()
{
	static bool FirstClick = true;

	if (TrexEngine::Input::mouse.IsRightClickPressed())
	{
		TrexEngine::Input::mouse.DisableCursor(m_Window->GetWindow(),true);
		if (FirstClick)
		{
			FirstClick = false;
			TrexEngine::Input::mouse.SetCursorPosition(m_Window->GetWindow(), m_Window->GetW()/2, m_Window->GetH()/2);
		}

		double Mx, My;
		TrexEngine::Input::mouse.GetCursorPosition(m_Window->GetWindow(), &Mx, &My);

		float rotX = 200.0f * (float)(My - (m_Window->GetH() / 2)) / m_Window->GetH();
		float rotY = 200.0f * (float)(Mx - (m_Window->GetW() / 2)) / m_Window->GetW();

		glm::vec3 NewOriantation = glm::rotate(TrexCamera.GetOriantation(), glm::radians(-rotX),
			glm::normalize(glm::cross(TrexCamera.GetOriantation(), TrexCamera.GetUP())));

		if (abs(glm::angle(NewOriantation, TrexCamera.GetUP()) - glm::radians(90.0f)) <= glm::radians(85.0f))
			TrexCamera.GetOriantation() = NewOriantation;
		

		TrexCamera.GetOriantation() = glm::rotate(TrexCamera.GetOriantation(), glm::radians(-rotY), TrexCamera.GetUP());
		TrexEngine::Input::mouse.SetCursorPosition(m_Window->GetWindow(), m_Window->GetW()/2, m_Window->GetH()/2);
	}

	else
	{
		if (!FirstClick)
		{
			TrexEngine::Input::mouse.DisableCursor(m_Window->GetWindow(), false);
			FirstClick = true;
			Log.SetInfo("Cursor Reseted to Normal");
		}
		
	}

}


ExampleLayer::~ExampleLayer()
{
}