/*

	Rewrote by: The Voltage
	Date: 2025/20/3

	Purpose:
		Creates a OpenGL Vertex Buffer Object and allows you to upload data to it and use it as needed.
*/


#pragma once

#include "../Core/Core.h"
#include "../3rdparty/GL/glew.h"
#include "VertexBufferLayout.h"

namespace TrexEngine
{

	class VertexBuffer
	{
	public:

		TX_API VertexBuffer();
		TX_API VertexBuffer(GLenum MemberType, int MemberPerVertex, int NumberOfVertecies);
		TX_API VertexBuffer(GLenum MemberType, int MemberPerVertex, int NumberOfVertecies, GLenum BufferUsage, void* Data);
		TX_API ~VertexBuffer();

		TX_API void UploadData(GLenum MemberType, int MemberPerVertex, int NumberOfVertecies, GLenum BufferUsage, void* Data);
		TX_API void DeleteBuffer();

		TX_API void Bind() const;
		TX_API void Unbind() const;

		TX_API inline bool IsBind() const { return m_IsBind; } 
		TX_API inline int GetMemberPerVertex() const { return m_MemberPerVertex; } 
		TX_API inline int GetNumberOfVertecies() const { return m_NumberOfVertecies; } 
		TX_API inline GLenum GetDataType()		const  { return m_MemberType; } 

	private:
		unsigned int m_VertexBufferID = 0;
		int m_MemberPerVertex = 0;
		int m_NumberOfVertecies = 0;
		GLenum m_MemberType;
		mutable bool m_IsBind = false;
	};

};
