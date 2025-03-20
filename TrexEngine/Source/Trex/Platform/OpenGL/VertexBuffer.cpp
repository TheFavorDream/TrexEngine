#include "VertexBuffer.h"
#include "Log.h"

namespace TrexEngine
{
	VertexBuffer::VertexBuffer()
	{
		GLCall(glGenBuffers(1, &m_VertexBufferID));
		Bind();
	}

	VertexBuffer::VertexBuffer(GLenum MemberType, int MemberPerVertex, int NumberOfVertecies)
	{
		GLCall(glGenBuffers(1, &m_VertexBufferID));
		Bind();
	}

	VertexBuffer::VertexBuffer(GLenum MemberType, int MemberPerVertex, int NumberOfVertecies, GLenum BufferUsage, void * Data)
	{
		GLCall(glGenBuffers(1, &m_VertexBufferID));
		Bind();
		UploadData(MemberType, MemberPerVertex, NumberOfVertecies, BufferUsage, Data);
	}

	VertexBuffer::~VertexBuffer()
	{
		DeleteBuffer();
	}

	TX_API void VertexBuffer::UploadData(GLenum MemberType, int MemberPerVertex, int NumberOfVertecies, GLenum BufferUsage, void * Data)
	{
		m_MemberType = MemberType;
		m_MemberPerVertex = MemberPerVertex;
		m_NumberOfVertecies = NumberOfVertecies;

		GLCall(glBufferData(GL_ARRAY_BUFFER, (m_MemberPerVertex*m_NumberOfVertecies)*Layout::GetTypeSize(m_MemberType), Data, BufferUsage));
	}

	TX_API void VertexBuffer::DeleteBuffer()
	{
		Unbind();
		GLCall(glDeleteBuffers(1, &m_VertexBufferID));
	}

	TX_API void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
		m_IsBind = true;
	}

	TX_API void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		m_IsBind = false;
	}
}