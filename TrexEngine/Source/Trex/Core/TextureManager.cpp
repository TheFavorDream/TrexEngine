
#include "TextureManager.h"


namespace TrexEngine
{

	TextureManager::TextureManager()
	{
		Logger::CoreLogger->SetInfo("Texture Manager Constructed");
	}

	TextureManager::~TextureManager()
	{
		Logger::CoreLogger->SetInfo("Texture Manager Destructed");

		for (auto &i : m_TextureTable)
		{
			delete i.second;
		}

	}

	int TextureManager::AddTexture(std::string Name, Texture * NewTexture)
	{
		if (Name == "")
		{
			Logger::CoreLogger->SetError("Texture Name cannot be empty");
			return 1;
		}

		if (m_TextureTable.find(Name) != m_TextureTable.end())
		{
			Logger::CoreLogger->SetError("The Texture '" + Name + "' Already exist.");
			return 2;
		}

		m_TextureTable[Name] = NewTexture;
		return 0;
	}

	int TextureManager::RemoveTexture(std::string Name)
	{
		if (!DoesTextureExist(Name))
		{
			Logger::CoreLogger->SetError(Name + " Textur does not exist");
			return 1;
		}

		delete m_TextureTable[Name];
		m_TextureTable.erase(Name);
		return 0;
	}

	TX_API int TextureManager::BindTexture(std::string Name, uint16 Slot)
	{
		m_TextureTable[Name]->Bind(Slot);
		return 0;
	}

	TX_API int TextureManager::UnbindTexture(std::string Name)
	{
		m_TextureTable[Name]->Unbind();
		return 0;
	}


	int TextureManager::UnloadTexture(std::string Name)
	{
		if (!DoesTextureExist(Name))
		{
			Logger::CoreLogger->SetError(Name + " Textur does not exist");
			return 1;
		}

		m_TextureTable[Name]->FreeTexture();
		return 0;
	}

	TX_API bool TextureManager::DoesTextureExist(std::string Name)
	{
		if (m_TextureTable.find(Name) != m_TextureTable.end())
		{
			return true;
		}
		return false;
	}

	Texture* TextureManager::GetTexture(std::string Name)
	{
		return m_TextureTable[Name];
	}

	void TextureManager::OnEyeOfTrex()
	{

	}

};