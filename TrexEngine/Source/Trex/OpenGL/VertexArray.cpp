#include "../Include/Renderer/OpenGL/VertexArray.h"
#include "../Include/Log.h"

namespace TrexEngine
{


	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1,&VertexArrayID));
		GLCall(glBindVertexArray(VertexArrayID));
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &VertexArrayID));
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(VertexArrayID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

	void VertexArray::AddLayouts(const VertexBuffer & VBO, VertexBufferLayout & VBL)
	{

		int Offset = 0;

		auto Layouts = VBL.GetLayouts();
		VBO.Bind();
		for (int i = 0; i < Layouts.size(); ++i)
		{
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, Layouts[i].m_Count, Layouts[i].m_Type, Layouts[i].m_Normalized, VBL.GetStride(), (void*)Offset));
			Offset += Layouts[i].m_Count * Layout::GetTypeSize(Layouts[i].m_Type);
		}
	}

};