/*
	Created by Voltage.
	E-mail: poyavoltage148@gmail.com

	Purpose:
	Resource Manager manages all the large size resources like textures, audios, shaders etc
	and keep track of their usage, so if a resource is unused it frees it from memory.
*/

#pragma once


#include "Core.h"
#include "../Debug/Log.h"

#include <vector>
#include <map>
#include <memory.h>
#include <stdio.h>


//The Maximum size that you can allocate for a BUFFER is 64MBs
#define MAX_SIZE 64 * 1024 * 1024 

namespace TrexEngine
{

	struct Resource
	{
		Resource() {}

		Resource(char* p_Data, uint32 p_Size)
			: Data(p_Data), Size(p_Size), AccessTime(0), LastAccess(0)
		{
			
		}


		//The Main Pointer to Data
		char* Data = NULL;

		//The Size of buffer
		uint32 Size = 0;

		//Stores how many time we used this resource.
		uint32 AccessTime = 0;

		//Stores the last time we used this resource.
		double LastAccess = 0;
	};

	class ResourceManager
	{
	public:

		//Automatic Init
		TX_API ResourceManager();
		//Automatic Shutdown
		TX_API ~ResourceManager();

		//Manual Init
		TX_API void Init();
		//Manual Shutdown
		TX_API void Shutdown();

		TX_API int AllocateMemory(std::string ID, uint32 SizeInBytes);
		TX_API int DeallocateMemory(std::string ID);

		TX_API int WriteMemory(std::string ID, int32 Offset, int8 Byte);
		TX_API int WriteMemory(std::string ID, int32 Offset, uint32 Size, void* Bytes);

		TX_API void* ReadMemory(std::string ID, int32 Start = 0);

		//looks up in ID table to see if the Resource exists or not  
		TX_API bool DoesResourceExist(std::string ID);


		TX_API uint32 MegsToBytes(uint32 Megs);

		TX_API uint32 KillosToBytes(uint32 Killos);


		TX_API inline uint16 NumberOfResources() { return ResourceIDs.size(); }
		TX_API const Resource& GetResourceByIndex(uint16 index, std::string& ID);

	private:

		int ResourceNumbers = 0;

		//All IDs stores in this vector;
		std::vector<std::string> ResourceIDs;

		//This hold pointers to resources and provide a interface to access them with their IDs;
		std::map<std::string, Resource> ResourceTable;

	};

};
