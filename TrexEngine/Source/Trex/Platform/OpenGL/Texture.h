/*
	Created by: The Voltage
	Data: 2025/4/11

	Purpose:
		A proper OpenGL Texture class. 
*/

#pragma once

#include "../../Core/Core.h"
#include "../../Debug/Log.h"
#include "../../3rdparty/GL/glew.h"
#include "../../3rdparty/stb_image/stb_image.h"

namespace TrexEngine
{
	//Base Texture Class
	class Texture
	{
	public:

		TX_API virtual ~Texture() = default;
		 


		TX_API virtual int LoadTexture(bool KeepTextureCache = false) = 0;
		TX_API virtual int FreeTexture() = 0;
		TX_API virtual int DeleteTexture() = 0;

		TX_API virtual inline unsigned int GetWidth() { return  m_Width; }
		TX_API virtual inline unsigned int GetHeight() { return m_Height; }
		TX_API virtual inline unsigned int GetTextureID() { return  m_TextureID; }
		
		TX_API inline uint64 GetAccessTime() { return m_AccessTime; }

		TX_API virtual void Bind(uint32 slot = 0) = 0;
		TX_API virtual void Unbind()			   = 0;

	protected:

		uint8* m_TextureData = nullptr;
		uint32 m_Width, m_Height, m_Channel;
		uint32 m_TextureID = 0;
		uint64 m_AccessTime;
		bool m_KeepTextureCache;
	};



	class Texture2D : public Texture
	{
	public:

		TX_API  Texture2D(std::string Path);
		TX_API ~Texture2D();
		
		TX_API int LoadTexture(bool KeepTextureCache) override;
		TX_API int FreeTexture() override;
		TX_API int DeleteTexture() override;

		TX_API void Bind(uint32 slot = 0) override;
		TX_API void Unbind() override;

	private:
		std::string m_Path;
	};


	class TextureCube : public Texture
	{
	public:
		TX_API  TextureCube(std::string& pSubDirectory, std::vector<std::string> pTextures);
		TX_API ~TextureCube();

		TX_API int LoadTexture(bool KeepTextureCache) override;
		TX_API int FreeTexture() override;
		TX_API int DeleteTexture() override;

		TX_API void Bind(uint32 slot = 0) override;
		TX_API void Unbind() override;

	private:
		std::string m_SubDirectory;
		std::vector<std::string> m_Textures;
	};
}