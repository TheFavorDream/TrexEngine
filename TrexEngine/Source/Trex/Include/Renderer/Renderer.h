#pragma once
#include "GL/glew.h"
#include "../Core.h"

#include "WindowManager.h"
#include "./OpenGL/IndexBuffer.h"
#include "./OpenGL/VertexArray.h"
#include "./OpenGL/VertexBuffer.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui.h"

namespace TrexEngine
{

	class  Renderer
	{
	public:

		TX_API static Renderer* GetInstance();

		Renderer(const Renderer& obj) = delete;

		TX_API int InitGLFW();

		TX_API int InitGLEW();

		TX_API void DrawArrays(const VertexBuffer& VBO,  const VertexArray& VAO) const;

		TX_API void DrawElements(const VertexBuffer& VBO, const IndexBuffer& EBO, const VertexArray& VAO) const;

		TX_API int Shutdown();

		TX_API ~Renderer();

	private:
		Renderer();

	public:
		static Renderer* Render;
	};

};