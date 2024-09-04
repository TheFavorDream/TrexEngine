#pragma once

#include "Core.h"
#include "../../GL/glew.h"
#include <vector>

namespace TrexEngine 
{


	struct Layout
	{
		unsigned int m_Type;
		unsigned int m_Count;
		unsigned char m_Normalized;

		static unsigned int GetTypeSize(unsigned int p_Type)
		{
			switch (p_Type)
			{
			case GL_FLOAT:			return sizeof(float);
			case GL_UNSIGNED_INT:	return sizeof(unsigned int);
			case GL_UNSIGNED_BYTE:  return sizeof(unsigned char);
			}
			return 0;
		}
	};

	class VertexBufferLayout
	{
	public:
		TX_API VertexBufferLayout()
			: m_Stride(0)
		{

		}


		template <typename T>
		void push(unsigned int m_Count)
		{

		}

		template <>
		void push<float>(unsigned int m_Count)
		{
			m_Layouts.push_back({ GL_FLOAT, m_Count, GL_FALSE });
			m_Stride += Layout::GetTypeSize(GL_FLOAT) * m_Count;
		}

		TX_API inline std::vector<Layout>& GetLayouts() { return m_Layouts; }

		TX_API inline unsigned int GetStride() { return m_Stride; }

	private:
		unsigned int m_Stride = 0;
		std::vector<Layout> m_Layouts;
	};

};