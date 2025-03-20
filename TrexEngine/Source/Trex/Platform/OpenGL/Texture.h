/*
	Created by: The Voltage
	Data: 2025/20/3

	Purpose:
		A proper OpenGL Texture class. 
*/

#pragma once

#include "../../Core/Core.h"
#include "../../3rdparty/GL/glew.h"
#include "../../3rdparty/stb_image/stb_image.h"

namespace TrexEngine
{
	class Texture
	{
	public:

		TX_API Texture();
		TX_API Texture(const char* FilePath);
		TX_API ~Texture();
		 
		TX_API void Bind(unsigned int slot = 0);
		TX_API void Unbind();
		 
		TX_API void LoadTexture(const char* FilePath);
		TX_API void FreeTexture();
		 
		TX_API inline unsigned int GetTextureID() { return m_Texture; }

	private:
		unsigned int m_Texture = 0;
		int m_Width, m_Height, m_BPP;
		unsigned char* m_Data = NULL;
	};
}