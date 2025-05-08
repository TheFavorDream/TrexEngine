
#include "Renderer.h"
#include "Log.h"

namespace TrexEngine
{

	Renderer* Renderer::s_RenderInstance = NULL;

	TX_API Renderer* Renderer::GetInstance()
	{
		if (s_RenderInstance == NULL)
		{
			s_RenderInstance = new Renderer;
		}

		return s_RenderInstance;
	}


	int Renderer::Init()
	{
		if (glewInit() != GLEW_OK)
		{
			Logger::CoreLogger->SetError("Unable to Init GLEW");
			return 1;
		}

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		return 0;
	}


	TX_API void Renderer::DrawArrays(const VertexBuffer & VBO, const VertexArray & VAO) const
	{
		VAO.Bind();
		VBO.Bind();
		GLCall(glDrawArrays(GL_TRIANGLES, 0, VBO.GetNumberOfVertecies()));
	}


	TX_API void Renderer::DrawElements(const VertexBuffer & VBO, const IndexBuffer & EBO, const VertexArray& VAO) const
	{
		VAO.Bind();
		VBO.Bind();
		EBO.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, EBO.GetCount(), GL_UNSIGNED_INT, NULL));
		return;
	}

	TX_API void Renderer::SetDepthSetting(GLenum pSetting)
	{
		GLCall(glDepthFunc(pSetting));
	}

	int Renderer::Shutdown()
	{

		return 0;
	}

	Renderer::~Renderer()
	{
		Shutdown();
	}

};