#include "Include/Renderer/Renderer.h"
#include "Log.h"

namespace TrexEngine
{

	Renderer::Renderer()
	{
		Logger::CoreLogger->SetInfo("Renderer Constructor Called");
	}

	int Renderer::InitGLFW()
	{
		if (!glfwInit())
		{
			Logger::CoreLogger->SetError("Unable to Init GLFW");
			return 1;
		}
		return 0;
	}

	int Renderer::InitGLEW()
	{
		if (glewInit() != GLEW_OK)
		{
			Logger::CoreLogger->SetError("Unable to Init GLEW");
			return 1;
		}
		return 0;
	}


	TX_API void Renderer::Draw(const VertexBuffer & VBO, const IndexBuffer & EBO, const VertexArray& VAO)
	{
		VAO.Bind();
		VBO.Bind();
		EBO.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
		VAO.Unbind();
		VBO.Unbind();
		EBO.Unbind();
		return;
	}

	int Renderer::Shutdown()
	{
		glfwTerminate();
		return 0;
	}

	Renderer::~Renderer()
	{
		Logger::CoreLogger->SetInfo("Renderer Destructor Called");
		Shutdown();
	}

};