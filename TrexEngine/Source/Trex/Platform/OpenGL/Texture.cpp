#include "Texture.h"


namespace TrexEngine
{
	Texture::Texture()
		: m_Texture(0), m_Width(0), m_Height(0), m_BPP(0), m_Data(nullptr)
	{

	}

	Texture::Texture(const char * FilePath)
		: m_Texture(0), m_Width(0), m_Height(0), m_BPP(0), m_Data(nullptr)
	{
		LoadTexture(FilePath);
		Bind();
	}

	Texture::~Texture()
	{
		FreeTexture();
	}



	void Texture::Bind(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::LoadTexture(const char * FilePath)
	{
		stbi_set_flip_vertically_on_load(true);
		m_Data = stbi_load(FilePath, &m_Width, &m_Height, &m_BPP, 4);

		glGenTextures(1, &m_Texture);
		Bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)m_Data);


	}

	void Texture::FreeTexture()
	{
		if (m_Data)
		{
			stbi_image_free(m_Data);
		}

		Unbind();
		glDeleteTextures(1, &m_Texture);
	}
}