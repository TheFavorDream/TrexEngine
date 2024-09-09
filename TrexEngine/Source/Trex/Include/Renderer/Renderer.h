#pragma once
#include "GL/glew.h"
#include "../Core.h"

#include "WindowManager.h"
#include "./OpenGL/IndexBuffer.h"
#include "./OpenGL/VertexArray.h"
#include "./OpenGL/VertexBuffer.h"

namespace TrexEngine
{

	class  Renderer
	{
	public:

		TX_API Renderer();

		TX_API int InitGLFW();

		TX_API int InitGLEW();


		TX_API static void Draw(const VertexBuffer& VBO, const IndexBuffer& EBO, const VertexArray& VAO);

		TX_API int Shutdown();

		TX_API ~Renderer();

	public:
		bool IsInit = false;
	};

};