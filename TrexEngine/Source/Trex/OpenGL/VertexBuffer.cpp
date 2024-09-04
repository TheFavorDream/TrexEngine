#include "../Include/Renderer/OpenGL/VertexBuffer.h"

namespace TrexEngine
{
	VertexBuffer::VertexBuffer(void* p_Data, unsigned int p_Size)
	{
		glGenBuffers(1, &VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, p_Size, p_Data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &VertexBufferID);
	}

	void VertexBuffer::Bind() const 
	{
		glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	}

	void VertexBuffer::Unbind() const 
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}