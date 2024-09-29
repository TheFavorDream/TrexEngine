#pragma once

#include "../Core/Core.h"
#include "../3rdparty/GL/glew.h"
#include "../Platform/OpenGL/VertexBuffer.h"
#include "../Platform/OpenGL/VertexBufferLayout.h"

namespace TrexEngine
{

	class VertexArray
	{

	public:

		TX_API VertexArray();

		TX_API ~VertexArray();

		TX_API void Bind() const;

		TX_API void Unbind() const;

		TX_API void AddLayouts(const VertexBuffer& VBO, VertexBufferLayout& VBL);

	private:
		unsigned int VertexArrayID = 0;
	};

};