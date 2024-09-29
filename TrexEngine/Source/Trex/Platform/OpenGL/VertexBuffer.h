#pragma once


#include "../Core/Core.h"
#include "../3rdparty/GL/glew.h"

namespace TrexEngine
{

	class VertexBuffer
	{
	public:

		TX_API VertexBuffer();

		TX_API void BufferData(void* p_Data, unsigned int p_Size);

		TX_API ~VertexBuffer();

		TX_API void Bind() const;

		TX_API void Unbind() const ;

	private:
		unsigned int VertexBufferID = 0;
	};

};
