#pragma once
#include "../3rdparty/GL/glew.h"
#include "../Core/Core.h"

#include "../Platform/OpenGL/IndexBuffer.h"
#include "../Platform/OpenGL/VertexArray.h"
#include "../Platform/OpenGL/VertexBuffer.h"

#include "../3rdparty/ImGui/Include/imgui.h"
#include "../3rdparty/ImGui/Include/imgui_impl_opengl3.h"
#include "../3rdparty/ImGui/Include/imgui.h"

namespace TrexEngine
{

	
	class  Renderer
	{
	public:

		TX_API static  Renderer* GetInstance();

		TX_API int Init();
		TX_API int Shutdown();

		TX_API void DrawArrays(const VertexBuffer& VBO,  const VertexArray& VAO) const;
		TX_API void DrawElements(const VertexBuffer& VBO, const IndexBuffer& EBO, const VertexArray& VAO) const;

		TX_API void SetDepthSetting(GLenum pSetting);

		TX_API ~Renderer();

	private:
		Renderer() {};
	public:
		static Renderer* s_RenderInstance;
	};


};