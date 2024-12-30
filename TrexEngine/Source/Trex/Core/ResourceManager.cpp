#include "ResourceManager.h"



namespace TrexEngine
{

	ResourceManager::ResourceManager() {	Init();  }

	ResourceManager::~ResourceManager() {	Shutdown(); }

	TX_API void ResourceManager::Init()
	{
		Logger::CoreLogger->SetInfo("Initializing Resource Manager");

	}

	TX_API void ResourceManager::Shutdown()
	{
		Logger::CoreLogger->SetInfo("Shuting down Resource Manager");
	}



	/*
	
		Allocates Raw Memory
	
	*/
	TX_API int ResourceManager::AllocateMemory(std::string ID, uint32 SizeInBytes)
	{
		if (DoesResourceExist(ID))
		{
			Logger::CoreLogger->SetError(ID + " already exists");
			return 1; 
		}

		if (SizeInBytes > MAX_SIZE)
		{
			Logger::CoreLogger->SetError("The Memory Allocation Limit is 64MBs");
			return 2;
		}

		//Allocate a new resource
		ResourceTable[ID].Data = new char[SizeInBytes];
		ResourceTable[ID].Size = SizeInBytes;

		ResourceIDs.push_back(ID);

		Logger::CoreLogger->SetInfo("\"" + ID + "\" Allocated with " + std::to_string(SizeInBytes) + " Bytes");

		return 0; // No Error
	}

	TX_API int ResourceManager::DeallocateMemory(std::string ID)
	{
		if (!DoesResourceExist(ID))
		{
			Logger::CoreLogger->SetError("\"" + ID + "\" does not exist");
			return 1;
		}

		delete[] ResourceTable[ID].Data;
		ResourceTable.erase(ID);
		return 0; // No Error
	}

	TX_API int ResourceManager::WriteMemory(std::string ID, int32 Offset, int8 Byte)
	{
		if (!DoesResourceExist(ID))
		{
			Logger::CoreLogger->SetError("\"" + ID + "\" does not exist");
			return 1;
		}

		if (Offset >= ResourceTable[ID].Size)
		{
			Logger::CoreLogger->SetError("\"" + ID + "\": Writing Out of bound");
			return 2;
		}

		*(ResourceTable[ID].Data + Offset) = Byte;
		return 0;//No Error;
	}

	TX_API int ResourceManager::WriteMemory(std::string ID, int32 Offset, uint32 Size, void* Bytes)
	{
		if (!DoesResourceExist(ID))
		{
			Logger::CoreLogger->SetError("\"" + ID + "\" does not exist");
			return 1;
		}

		if (Offset > ResourceTable[ID].Size - Size)
		{
			Logger::CoreLogger->SetError("\"" + ID + "\": Writing Out of bound");
			return 2;
		}

		std::memcpy((void*)ResourceTable[ID].Data, Bytes, Size);
		return 0;
	}

	TX_API void* ResourceManager::ReadMemory(std::string ID, int32 Start)
	{
		if (!DoesResourceExist(ID))
		{
			Logger::CoreLogger->SetError("\"" + ID + "\" does not exist");
			return NULL;
		}
		
		ResourceTable[ID].AccessTime += 1;
		ResourceTable[ID].LastAccess = Timer::GetCurrentElapsed();
		return (void*)(ResourceTable[ID].Data + Start);
	}


	//ToDo: Make this shitty algorithem faster.
	TX_API bool ResourceManager::DoesResourceExist(std::string ID)
	{
		for (int i = 0; i < ResourceIDs.size(); ++i)
		{
			if (ResourceIDs[i] == ID)
			{
				return true;
			}
		}
		return false;
	}


	TX_API uint32 ResourceManager::MegsToBytes(uint32 Megs) 
	{
		return Megs * 1024 * 1024; 
	}

	TX_API uint32 ResourceManager::KillosToBytes(uint32 Killos) 
	{ 
		return Killos * 1024; 
	}

	TX_API const Resource & ResourceManager::GetResourceByIndex(uint16 index, std::string& ID)
	{
		if (index >= ResourceIDs.size())
			ASSERT("Out of Range");

		ID = ResourceIDs[index];
		return ResourceTable[ID];
	}

};