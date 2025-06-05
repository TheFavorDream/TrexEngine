#include ".\Include\Wednesdex.h"
#include <filesystem>


Wednesdex::Wednesdex()
	: Layer("Wednesdex"), Log("Wednesdex"), TrexCamera({ 0.0f, 0.0f, 5.0f }, 45)
{
#ifdef RELEASE
	Log.SetLogLevel(TX_L0);
#endif
	m_Engine = TrexEngine::Engine::Get();


}


void Wednesdex::OnAttach()
{

	Log.SetInfo("Initalizing");

	//Cube Object
	CreateSphere(5.0f, VBO, VAO, EBO);

	//Skybox
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


	m_Engine->TexturesManager->AddTexture("Container", new Texture2D(T + "container.png"));
	m_Engine->TexturesManager->AddTexture("ContainerBoarder", new Texture2D(T + "container_boarder.png"));


	m_Engine->TexturesManager->AddTexture("Skybox", new TextureCube((T + "skybox/"), {"Right.jpg", "Left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"}));


	m_Engine->ShadersManager->GetCurrentShader()->SetUniformI1("Diffuse", 0);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformI1("Specular", 1);

	

	
	m_Engine->TexturesManager->GetTexture("Container")->LoadTexture();
	m_Engine->TexturesManager->GetTexture("ContainerBoarder")->LoadTexture();

	m_Engine->TexturesManager->GetTexture("Skybox")->LoadTexture();

	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

}


void Wednesdex::OnEvent()
{
	
	CameraKeyControll();
	CameraMouseControll();
}

void Wednesdex::OnUpdate()
{


	glm::mat4& Projection = TrexCamera.GetProjection(0.1f, 800.0f, m_Engine->WindowManager->GetW(), m_Engine->WindowManager->GetH());


	float Now = (float)TrexEngine::Timer::GetCurrentElapsed() / 1000;
	
	model = glm::mat4(1.0f);
	
	//LightPosition = glm::vec3((cosf(Now)*sinf(Now))*30.0f, (sinf(Now)*30.0f) + 12.0f, cosf(Now)*30.0f);
	LightPosition.z = 30.0f * sinf(Now) + 30.0f;
	m_Engine->ShadersManager->BindShader("Light");
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("Model", (model));
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("Projection", (Projection));
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformF3("LightColor", LightColor.x, LightColor.y, LightColor.z);


	m_Engine->ShadersManager->BindShader("Sphere");
	SphereModel = glm::mat4(1.0f);
	//SphereModel = glm::rotate(SphereModel, float(TrexEngine::Timer::GetCurrentElapsed()/1000), glm::vec3(0.0f, 1.0f, 0.0f));

	m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("Model", SphereModel);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("Projection", Projection);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformF3("ViewPosition", TrexCamera.GetCameraPosition().x, TrexCamera.GetCameraPosition().y, TrexCamera.GetCameraPosition().z);

	m_Engine->ShadersManager->GetCurrentShader()->SetUniformF3("meterial.Color", 0.3f, 0.0f, 0.5f);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformI1("meterial.Texture", 0);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformF1("meterial.Shininess", 32.0f);

	m_Engine->ShadersManager->GetCurrentShader()->SetUniformF3("light.Position", LightPosition.x, LightPosition.y, LightPosition.z);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformF3("light.Color", LightColor.x, LightColor.y, LightColor.z);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformF1("light.Constant", 1.0f);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformF1("light.Linear", 0.00045f);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformF1("light.Quadratic", 0.00034f);


	m_Engine->ShadersManager->BindShader("Skybox");
	glm::mat4 View = glm::mat4(glm::mat3(TrexCamera.GetView()));
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("View_Projection", (Projection*View));
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformI1("skybox", 0);


}

void Wednesdex::OnRender()
{

	//Light

	VBO.Bind();
	VAO.Bind();
	m_Engine->ShadersManager->BindShader("Light");
	glm::mat4 View = TrexCamera.GetView();
	View = glm::translate(View, LightPosition);
	m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("View", (View));
	TrexEngine::Renderer::GetInstance()->DrawElements(VBO, EBO, VAO);


	//Object
	VBO.Bind();
	VAO.Bind();
	m_Engine->ShadersManager->BindShader("Sphere");	
	for (int i = 0; i < 3; i++)
	{
		m_Engine->ShadersManager->GetCurrentShader()->SetUniformF3("meterial.Color", (i==0), (i==1), (i==2));

		View = TrexCamera.GetView();
		View = glm::translate(View, Coords[i]);
		m_Engine->ShadersManager->GetCurrentShader()->SetUniformMat4("View", (View));
		TrexEngine::Renderer::GetInstance()->DrawElements(VBO, EBO,  VAO);
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


void Wednesdex::OnDettach()
{

	Log.SetInfo("Shuting Down");

	Log.Shutdown();
}

void Wednesdex::EnableLayer()
{
	Enable = true;
	Log.SetWarning(LayerName + " got enabled");
}

void Wednesdex::DisableLayer()
{
	Enable = false;
	Log.SetWarning(LayerName + " got disabled");

}

void Wednesdex::CameraKeyControll()
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

void Wednesdex::CameraMouseControll()
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

		float MouseX = (float(PosXin) - LastX);
		float MouseY = (LastY - float(PosYin));


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

void Wednesdex::CreateSphere(float radius,VertexBuffer & VBO, VertexArray & VAO, IndexBuffer & EBO)
{

	std::vector<float> Vertecies;

	float Pi = 3.14159f;
	int StackCount = 50;
	int SectorCount = 50;


	float x, y, z, xy;                              // vertex position
	float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
	float s, t;                                     // vertex texCoord

	float sectorStep = 2 * Pi / SectorCount;
	float stackStep = Pi / StackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= StackCount; ++i)
	{
		stackAngle = Pi / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// first and last vertices have same position and normal, but different tex coords
		for (int j = 0; j <= SectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position (x, y, z)
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			Vertecies.push_back(x);
			Vertecies.push_back(y);
			Vertecies.push_back(z);

			// normalized vertex normal (nx, ny, nz)
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			Vertecies.push_back(nx);
			Vertecies.push_back(ny);
			Vertecies.push_back(nz);

			// vertex tex coord (s, t) range between [0, 1]
			s = (float)j / SectorCount;
			t = (float)i / StackCount;
			Vertecies.push_back(s);
			Vertecies.push_back(t);
		}
	}

	std::vector<unsigned int> indices;

	int k1, k2;
	for (int i = 0; i < StackCount; ++i)
	{
		k1 = i * (SectorCount + 1);     // beginning of current stack
		k2 = k1 + SectorCount + 1;      // beginning of next stack

		for (int j = 0; j < SectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding first and last stacks
			// k1 => k2 => k1+1
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			// k1+1 => k2 => k2+1
			if (i != (StackCount - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}

		}
	}

	VAO.Bind();
	VBO.Bind();
	VBO.UploadData(GL_FLOAT, 8, Vertecies.size()/8, GL_STATIC_DRAW, (void*)Vertecies.data());
	EBO.BufferData(indices.data(), indices.size());
	
	VertexBufferLayout VBL;
	VBL.push<float>(3);
	VBL.push<float>(3);
	VBL.push<float>(2);
	VAO.AddLayouts(VBO, VBL);
}




Wednesdex::~Wednesdex()
{
}
