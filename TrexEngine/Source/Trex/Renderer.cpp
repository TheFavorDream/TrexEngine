#include "Include/Renderer/Renderer.h"
#include "Log.h"

namespace TrexEngine
{

	Renderer::Renderer()
	{
		Logger::CoreLogger->SetInfo("Renderer Constructor Called");
	}

	Renderer *Renderer::Render;

	TX_API Renderer* Renderer::GetInstance()
	{
		if (Render == NULL)
		{
			Render = new Renderer;
		}


		return Render;
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

	TX_API void Renderer::DrawArrays(const VertexBuffer & VBO, const VertexArray & VAO) const
	{
		VAO.Bind();
		VBO.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
	}


	TX_API void Renderer::DrawElements(const VertexBuffer & VBO, const IndexBuffer & EBO, const VertexArray& VAO) const
	{
		VAO.Bind();
		VBO.Bind();
		EBO.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, NULL));
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