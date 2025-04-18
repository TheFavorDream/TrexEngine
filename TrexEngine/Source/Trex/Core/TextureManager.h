/*

	Created by: The Voltage
	Date: 2025/3/22

	Purpose:
		TrexEngine's Texture manager is a system that controls and manages Textures.
		Resource Manager has a future called 'The Eye of Trex' which is a mechanism that keeps track of Texture usage.
		if a particular resource isn't used for a period of time, The Eye Of Trex will unload it from memory. 
		For Example, you Load a Texture, There will be two instance of the object, one on the CPU memory(RAM) and one on GPU(VRAM)
		if that Texture isn't used, we will delete the one that is on GPU. but the one of CPU remains untouched, so we can load it back if needed.

*/


#pragma once


#include "Core.h"
#include "../Debug/Log.h"
#include "../3rdparty/GL/glew.h"
#include "../Platform/OpenGL/Texture.h"

#include <unordered_map>
#include <vector>

namespace TrexEngine
{

	class TextureManager
	{
	public:
		TX_API  TextureManager();
		TX_API ~TextureManager();


		TX_API int AddTexture(std::string Name, Texture* NewTexture);
		TX_API int RemoveTexture(std::string Name);
		TX_API int BindTexture(std::string Name, uint16 Slot=0);
		TX_API int UnbindTexture(std::string Name);
		TX_API int UnloadTexture(std::string Name);

		TX_API bool DoesTextureExist(std::string Name);

		TX_API Texture* GetTexture(std::string Name);
		TX_API void OnEyeOfTrex();

		TX_API inline std::unordered_map<std::string, TrexEngine::Texture*>& GetTextureTable() { return m_TextureTable; }
			
	private:
		std::unordered_map<std::string, TrexEngine::Texture*> m_TextureTable;
	};

}