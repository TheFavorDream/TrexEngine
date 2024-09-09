#include "../Include/Renderer/OpenGL/IndexBuffer.h"
#include "../Include/Log.h"

namespace TrexEngine
{

	IndexBuffer::IndexBuffer(unsigned int *p_Data, unsigned int p_Count)
	{
		GLCall(glGenBuffers(1, &IndexBufferID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (p_Count * sizeof(unsigned int)), p_Data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &IndexBufferID));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID));
	}

	void IndexBuffer::Unbind() const 
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

};