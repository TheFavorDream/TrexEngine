#include "../Include/Renderer/OpenGL/VertexBuffer.h"
#include "../Include/Log.h"

namespace TrexEngine
{
	VertexBuffer::VertexBuffer()
	{
		GLCall(glGenBuffers(1, &VertexBufferID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID));
	}
	void VertexBuffer::BufferData(void* p_Data, unsigned int p_Size)
	{
		GLCall(glBufferData(GL_ARRAY_BUFFER, p_Size, p_Data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &VertexBufferID));
	}

	void VertexBuffer::Bind() const 
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID));
	}

	void VertexBuffer::Unbind() const 
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}