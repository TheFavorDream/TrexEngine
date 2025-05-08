#include ".\Include\ExampleLayer.h"
#include <filesystem>


ExampleLayer::ExampleLayer()
	: Layer("ExampleLayer"), Log("ExampleLayer"), TrexCamera({ 0.0f, 0.0f, 5.0f }, 45)
{
#ifdef RELEASE
	Log.SetLogLevel(TX_L0);
#endif
	m_Engine = TrexEngine::Engine::Get();


}


void ExampleLayer::OnAttach()
{


	VAO.Bind();
	VBO.Bind();
	VBO.UploadData(GL_FLOAT, 5, 24, GL_STATIC_DRAW, (void*)Vertex);
	VBO.Bind();
	VBL.push<float>(3);
	VBL.push<float>(2);
	EBO.BufferData(Indicies, 36);
	VAO.AddLayouts(VBO, VBL);



	SkyVAO.Bind();
	SkyVBO.Bind();
	SkyVBO.UploadData(GL_FLOAT, 3, 36, GL_STATIC_DRAW, (void*)SkyBoxVertex);
	SkyVBO.Bind();
	SkyVBL.push<float>(3);

	SkyVAO.AddLayouts(SkyVBO, SkyVBL);

	std::string T = "../../../Sandbox/Resources/";
	if (IsDebuggerPresent())
	{
		T = "./Resources/";
	}


	m_Engine->TexturesManager->AddTexture("Wall", new Texture2D(T+"wall.jpg"));
	m_Engine->TexturesManager->AddTexture("Container", new Texture2D(T + "container.jpg"));
	m_Engine->TexturesManager->AddTexture("Skybox", new TextureCube((T + "skybox/"), {"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"}));


	m_Engine->ShadersManager->GetCurrentShader()->SetUniformI1("Tex", 0);
	
	m_Engine->TexturesManager->GetTexture("Wall")->LoadTexture();
	m_Engine->TexturesManager->GetTexture("Container")->LoadTexture();
	m_Engine->TexturesManager->GetTexture("Skybox")->LoadTexture();

	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

}


void ExampleLayer::OnEvent()
{
	
	CameraKeyControll();
	CameraMouseControll();
}

void ExampleLayer::OnUpdate()
{


	glm::mat4& Projection = TrexCamera.GetProjection(0.1f, 100.0f, m_Engine->WindowManager->GetW(), m_Engine->WindowManager->GetH());

	if (TrexEngine::Input::keyboard.IsKeyPressed(TX_KEY_LEFT))
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	if (TrexEngine::Input::keyboard.IsKeyPressed(TX_KEY_UP))
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	if (TrexEngine::Input::keyboard.IsKeyPressed(TX_KEY_RIGHT))
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	//m_Engine->ShadersManager->BindShader("Test2");
	//m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("model", (model));
	//m_Engine->ShadersManager->GetCurrentShader()->SetUniformF3("cameraPos", TrexCamera.GetCameraPosition().x, TrexCamera.GetCameraPosition().y, TrexCamera.GetCameraPosition().z);
	//m_Engine->ShadersManager->GetCurrentShader()->SetUniformI1("skybox", 0);

	m_Engine->ShadersManager->BindShader("Main");
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("Model", (model));
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("Projection", (Projection));

	m_Engine->ShadersManager->BindShader("Skybox");
	glm::mat4 View = glm::mat4(glm::mat3(TrexCamera.GetView()));
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("View_Projection", (Projection*View));
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformI1("skybox", 0);


}

void ExampleLayer::OnRender()
{
	VBO.Bind();
	VAO.Bind();
	m_Engine->ShadersManager->BindShader("Main");
	for (int i = 0; i < 20; i++)
	{
		glm::mat4 View = TrexCamera.GetView();
		View = glm::translate(View, Coords[i]);
		m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("View", (View));
		if (i % 2 == 0)
			m_Engine->TexturesManager->BindTexture("Wall");
		else
			m_Engine->TexturesManager->BindTexture("Container");

		TrexEngine::Renderer::GetInstance()->DrawElements(VBO, EBO, VAO);
		//TrexEngine::Renderer::GetInstance()->DrawArrays(VBO, VAO);
	}
	
	//SkyBox;

	SkyVBO.Bind();
	SkyVAO.Bind();
	m_Engine->ShadersManager->BindShader("Skybox");
	m_Engine->TexturesManager->BindTexture("Skybox");

	TrexEngine::Renderer::GetInstance()->SetDepthSetting(GL_LEQUAL); 
	TrexEngine::Renderer::GetInstance()->DrawArrays(SkyVBO, SkyVAO);
	TrexEngine::Renderer::GetInstance()->SetDepthSetting(GL_LESS);

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
	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_W))
	{
		TrexCamera.Move(CAM_FRONT);
	}

	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_S))
	{
		TrexCamera.Move(CAM_BACK);
	}

	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_A))
	{
		TrexCamera.Move(CAM_LEFT);
	}

	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_D))
	{
		TrexCamera.Move(CAM_RIGHT);
	}

	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_SPACE))
	{
		TrexCamera.Move(CAM_UP);
	}

	if (m_Engine->events.keyboard.IsKeyPressed(TX_KEY_LEFT_CONTROL))
	{
		TrexCamera.Move(CAM_DOWN);
	}
}

void ExampleLayer::CameraMouseControll()
{
	static bool FirstClick = true;
	static float LastX = m_Engine->WindowManager->GetW()/2.0f;
	static float LastY = m_Engine->WindowManager->GetH() / 2.0f;

	if (TrexEngine::Input::mouse.IsRightClickPressed())
	{
		m_Engine->events.mouse.DisableCursor(m_Engine->WindowManager->GetWindow(), true);
		
		double PosXin, PosYin;
		PosXin = m_Engine->events.mouse.GetMouseX();
		PosYin = m_Engine->events.mouse.GetMouseY();

		if (FirstClick)
		{
			LastX = (float)PosXin;
			LastY = (float)PosYin;
			FirstClick = false;
		}

		float MouseX = (PosXin - LastX);
		float MouseY = (LastY - PosYin);


		TrexCamera.MouseMove(MouseX, MouseY);
		LastX = PosXin;
		LastY = PosYin;
	}

	else
	{
		if (!FirstClick)
		{
			TrexEngine::Input::mouse.DisableCursor(m_Engine->WindowManager->GetWindow(), false);
			FirstClick = true;
			Log.SetInfo("Cursor Reseted to Normal");
		}
		
	}

}


ExampleLayer::~ExampleLayer()
{
}