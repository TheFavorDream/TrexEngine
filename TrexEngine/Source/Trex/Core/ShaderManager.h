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

		TX_API ShaderManager(std::string p_Name, TrexEngine::Shader* p_NewShader);
		TX_API ShaderManager();

		TX_API ~ShaderManager();

		TX_API bool DoesShaderExist(std::string p_Name);
		TX_API int AddShader(std::string p_Name, TrexEngine::Shader* p_NewShader);
		TX_API int BindShader(std::string p_Name);
		TX_API int UnbindCurrent();
		TX_API int DeleteShader(std::string p_Name);
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