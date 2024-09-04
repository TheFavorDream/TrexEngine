#include "../Include/Renderer/OpenGL/VertexArray.h"

namespace TrexEngine
{


	VertexArray::VertexArray()
	{
		glGenVertexArrays(1,&VertexArrayID);
		glBindVertexArray(VertexArrayID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &VertexArrayID);
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(VertexArrayID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddLayouts(const VertexBuffer & VBO, VertexBufferLayout & VBL)
	{

		unsigned int Ofset = 0;

		auto Layouts = VBL.GetLayouts();
		VBO.Bind();
		for (int i = 0; i < Layouts.size(); ++i)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, Layouts[i].m_Count, Layouts[i].m_Type, Layouts[i].m_Normalized, VBL.GetStride(), (void*)Ofset);
			Ofset += Layouts[i].m_Count * Layout::GetTypeSize(Layouts[i].m_Type);
		}
	}

};