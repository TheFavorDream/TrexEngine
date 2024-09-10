
#include <iostream>
#include "Source/Trex.h"
class Application : public TrexEngine::Engine
{
public:
	Application(const char* p_Title, int p_Width, int p_Height)
		: Engine(p_Title, p_Width, p_Height),
		ApplicationLogger("SandBox")
	{
		ApplicationLogger.SetInfo("SandBox Constructor Called");

		VBL.push<float>(2);
		VBL.push<float>(3);

		VBO.BufferData(Vertices, sizeof(Vertices));

		VAO.AddLayouts(VBO, VBL);

		EBO.BufferData(Indicies, 6);


	}

	void Event() override
	{

	}

	void Update() override
	{
		switch (Increace)
		{
		case true:
			i += 0.0001f;


			if (i >= 1.0f)
			{
				Increace = false;
			}

			break;
		case false:
			i -= 0.0001f;

			if (i <= 0.0f)
			{
				Increace = true;
			}
			break;
		}

	}


	void Render() override
	{
		m_Shader.SetUniformF("u_Color", i);
		m_Shader.SetUniformF("Scale", i);
		m_Renderer.DrawElements(VBO, EBO, VAO);

	}


	~Application() 
	{
		ApplicationLogger.SetInfo("SandBox Destructor called");
	}


private:
	TrexEngine::Logger ApplicationLogger;


	TrexEngine::VertexArray        VAO;
	TrexEngine::VertexBufferLayout VBL;
	TrexEngine::VertexBuffer       VBO;
	TrexEngine::IndexBuffer        EBO;

	float Vertices[20] =
	{
		-0.5f, -0.5f,		1.0f, 0.5f, 0.5f,
		 0.5f, -0.5f,		0.5f, 1.0f, 0.0f,
		-0.5f,  0.5f,		0.2f, 0.5f, 1.0f,
		 0.5f,  0.5f,		1.0f, 0.5f, 0.2f
	};

	float i = 0.0f;
	bool Increace = true;

	unsigned int Indicies[6] =
	{
		0, 1, 2,
		1, 2, 3
	};

};



TrexEngine::Engine* TrexEngine::CreateApplication()
{
	return new Application("SandBox", 1000, 500);
}