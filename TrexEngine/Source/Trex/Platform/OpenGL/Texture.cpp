
#include "Texture.h"


namespace TrexEngine
{
	Texture2D::Texture2D(std::string Path)
	{
		m_Path = Path;
	}

	Texture2D::~Texture2D()
	{
		DeleteTexture();
	}


	int Texture2D::LoadTexture(bool KeepTextureCache)
	{

		if (m_TextureData == nullptr)
		{
			stbi_set_flip_vertically_on_load(true);

			int Width, Height, m_BPP;
			m_TextureData = stbi_load(m_Path.c_str(), &Width, &Height, &m_BPP, 4);

			if (m_TextureData == NULL)
			{
				return 1;
			}

			m_Width = Width;
			m_Height = Height;
			m_Channel = m_BPP;
		}

		GLCall(glGenTextures(1, &m_TextureID));
		Bind(0);


		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)m_TextureData));

		if (!KeepTextureCache)
		{
			stbi_image_free(m_TextureData);
			m_TextureData = nullptr;
		}

		return 0;
	}

	int Texture2D::FreeTexture()
	{
		Unbind();
		GLCall(glDeleteTextures(1, &m_TextureID));
		m_TextureID = 0;
		return 0;
	}

	int Texture2D::DeleteTexture()
	{
		FreeTexture();

		if (!m_TextureData)
		{
			stbi_image_free(m_TextureData);
		}
		return 0;
	}

	void Texture2D::Bind(uint32 slot)
	{

		m_AccessTime = TrexEngine::Timer::GetCurrentElapsedUint();
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	}

	void Texture2D::Unbind() 
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

//Cube Textures

	TextureCube::TextureCube(std::string & pSubDirectory, std::vector<std::string> pTextures)
	{
		m_SubDirectory = pSubDirectory;
		m_Textures = pTextures;
		if (pTextures.size() < 6)
		{
			Logger::CoreLogger->SetWarning("not enough textures provided to cube texture");
		}
	}

	TextureCube::~TextureCube()
	{
		DeleteTexture();
	}

	int TextureCube::LoadTexture(bool KeepTextureCache)
	{
		GLCall(glGenTextures(1, &m_TextureID));
		Bind();


		stbi_set_flip_vertically_on_load(false);
		int Width, Height, Channels;

		for (int i = 0; i < m_Textures.size(); i++)
		{
			unsigned char* Face_Data = stbi_load((m_SubDirectory + m_Textures[i]).c_str(), &Width, &Height, &Channels, 0);
		
			if (!Face_Data)
			{
				Logger::CoreLogger->SetError("Failed to Texture at " + m_Textures[i]);
				stbi_image_free(Face_Data);
				continue;
			}

			GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Face_Data));
			stbi_image_free(Face_Data);

			GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			
			GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
			GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		}
		return 0;
	}
	
	int TextureCube::FreeTexture()
	{
		Unbind();
		GLCall(glDeleteTextures(1, &m_TextureID));
		m_TextureID = 0;
		return 0;
	}
	
	int TextureCube::DeleteTexture()
	{
		return FreeTexture();
	}
	
	void TextureCube::Bind(uint32 slot)
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID));
	}
	
	void TextureCube::Unbind()
	{
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}
}