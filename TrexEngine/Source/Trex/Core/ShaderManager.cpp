#include "ShaderManager.h"

namespace TrexEngine
{

	ShaderManager::ShaderManager()
	{

	}

	ShaderManager::ShaderManager(std::string p_Name, TrexEngine::Shader * p_NewShader)
	{
		AddShader(p_Name, p_NewShader);
	}

	ShaderManager::~ShaderManager()
	{
		for (auto &i : m_ShaderList)
		{
			delete m_Shaders[i];
		}


		m_Shaders.clear();
		m_ShaderList.clear();
		Logger::CoreLogger->SetInfo("End of Shader Manager Constructor");
	}


	//ToDo: Make this garbage faster
	TX_API bool ShaderManager::DoesShaderExist(std::string p_Name)
	{
		for (auto &i : m_ShaderList)
		{
			if (p_Name == i)
			{
				return true;
			}
		}
		return false;
	}

	TX_API int ShaderManager::AddShader(std::string p_Name, TrexEngine::Shader * p_NewShader)
	{
		if (p_NewShader == NULL)
		{
			Logger::CoreLogger->SetError("Shader Cannot be NULL");
			return 1;
		}

		if (p_Name.length() == 0)
		{
			Logger::CoreLogger->SetError("Shader Name Cannot be empty!");
			return 2;
		}

		if (DoesShaderExist(p_Name))
		{
			Logger::CoreLogger->SetError("The Shader :" + p_Name + " already exists");
			return 3;
		}

		//If we get here, we are good

		m_ShaderList.push_back(p_Name);
		m_Shaders[p_Name] = p_NewShader;

		BindShader(p_Name);

		return 0;
	}

	TX_API int ShaderManager::BindShader(std::string p_Name)
	{
		m_Current = m_Shaders[p_Name];
		m_Shaders[p_Name]->Bind();
		return 0;
	}

	TX_API int ShaderManager::UnbindCurrent()
	{
		m_Current->Unbind();
		return 0;
	}

	TX_API int ShaderManager::DeleteShader(std::string p_Name)
	{
		if (!DoesShaderExist(p_Name))
		{
			Logger::CoreLogger->SetError("Shader :" + p_Name + " Does Not Exist to delete");
			return 1;
		}

		if (m_Shaders[p_Name] == m_Current)
		{
			delete m_Current;
			m_Current = NULL;
		}
		else
			delete m_Shaders[p_Name];


		//m_Shaders.emplace(p_Name);
		for (int i = 0; i < m_ShaderList.size(); ++i)
		{
			if (m_ShaderList.at(i) == p_Name)
			{
				m_ShaderList.emplace(m_ShaderList.begin() + i);
				return 0;
			}
		}
		return 0;
	}

	TX_API const std::vector<std::string>& ShaderManager::GetShaderList()
	{
		return m_ShaderList;
	}

	TX_API TrexEngine::Shader * ShaderManager::GetCurrentShader()
	{
		return m_Current;
	}

	TX_API TrexEngine::Shader * ShaderManager::GetShader(std::string p_Name)
	{
		return m_Shaders[p_Name];
	}



}
