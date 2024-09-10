#pragma once


#include "../../Core.h"
#include "../../GL/glew.h"

namespace TrexEngine
{

	class IndexBuffer
	{
	public:

		TX_API IndexBuffer();

		TX_API void BufferData(unsigned int *p_Data, unsigned int p_Count);

		TX_API ~IndexBuffer();

		TX_API void Bind() const;

		TX_API void Unbind() const;

		TX_API inline unsigned int GetCount() const { return m_Count; }

	private:
		unsigned int m_Count = 0;
		unsigned int IndexBufferID = 0;
	};

};