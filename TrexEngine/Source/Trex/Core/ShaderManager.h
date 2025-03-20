/*
	Creator: The Voltage
	On: 2025/3/20

	purpose:
		This System will take care of managing shaders.
		Tasks like: Adding, Removing, Unloading, Accessing
*/



#pragma once
#include "../Platform/OpenGL/Shader.h"
#include "Core.h"
#include "../Debug/Log.h"
#include <unordered_map>
#include <vector>



namespace TrexEngine
{
	class ShaderManager
	{
	public:

		//Constructor that also adds a shader:
		TX_API ShaderManager(std::string p_Name, TrexEngine::Shader* p_NewShader);
		//Initalize only constructor:
		TX_API ShaderManager();
		//Destructor:
		TX_API ~ShaderManager();

		//Checks if the following shader exists or not:
		TX_API bool DoesShaderExist(std::string p_Name);

		//Adds a new shader and binds it and makes it current:
		TX_API int AddShader(std::string p_Name, TrexEngine::Shader* p_NewShader);
		//Binds a Shader and makes it current, if doesn't exist, returns 1
		TX_API int BindShader(std::string p_Name);
		//Unbinds currently binded shader
		TX_API int UnbindCurrent();
		//Deletes a shader from hashmap
		TX_API int DeleteShader(std::string p_Name);

		//Data Accessing methods:
		TX_API const std::vector<std::string>& GetShaderList();
		TX_API TrexEngine::Shader* GetCurrentShader();
		TX_API TrexEngine::Shader* GetShader(std::string p_Name);

	private:
		std::unordered_map<std::string, TrexEngine::Shader*> m_Shaders;
		std::vector<std::string> m_ShaderList;
		TrexEngine::Shader* m_Current = NULL;
	};

	static ShaderManager* s_Ref;
};