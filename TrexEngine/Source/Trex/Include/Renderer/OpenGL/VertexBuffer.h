#pragma once


#include "Core.h"
#include "../../GL/glew.h"

namespace TrexEngine
{

	class VertexBuffer
	{
	public:
		TX_API VertexBuffer(void* p_Data, unsigned int p_Size);

		TX_API ~VertexBuffer();

		TX_API void Bind() const;

		TX_API void Unbind() const ;

	private:
		unsigned int VertexBufferID = 0;
	};

};
