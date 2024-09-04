#pragma once


#include "Core.h"
#include "../../GL/glew.h"

namespace TrexEngine
{

	class IndexBuffer
	{
	public:

		TX_API IndexBuffer(unsigned int *p_Data, unsigned int p_Count);

		TX_API ~IndexBuffer();

		TX_API void Bind();

		TX_API void Unbind();

	private:

		unsigned int IndexBufferID = 0;
	};

};