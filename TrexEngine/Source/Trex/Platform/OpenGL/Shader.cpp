
#include "Shader.h"


namespace TrexEngine
{

	Shader::Shader(const std::string& pFilePath)
		: m_ShaderFilePath(pFilePath)
	{
		std::string Content = ReadFile(pFilePath);
		Process(Content);
		CreateShaderProgram();
	}

	Shader::Shader(const std::string& pVertexShader, const std::string& pFragmentShader)
	{
		m_Shaders[GL_VERTEX_SHADER] = pVertexShader;
		m_Shaders[GL_FRAGMENT_SHADER] = pFragmentShader;
		CreateShaderProgram();
	}

	Shader::~Shader()
	{
		if (m_ProgramID!=0)
			GLCall(glDeleteProgram(m_ProgramID));
	}


	void Shader::Bind()
	{
		GLCall(glUseProgram(m_ProgramID));
	}


	void Shader::Unbind()
	{
		GLCall(glUseProgram(0));
	}

	const std::string Shader::ReadFile(const std::string & pFilePath)
	{
		//Opening the file
		std::ifstream Source(pFilePath, std::ios::in | std::ios::binary);

		//Check if it opened
		if (Source.fail())
		{
			Logger::CoreLogger->SetError("Could not open shader file");
			return "";
		}

		std::string Content;

		//Allocate memory 
		Source.seekg(0, Source.end);
		Content.resize(Source.tellg());
		Source.seekg(0, Source.beg);

		//Read
		Source.read(&Content[0], Content.size());
		Source.close();

		return Content;
	}



	GLenum Shader::GetShaderEnum(const std::string & pType)
	{
		if (!pType.compare("Vertex\r"))
		{
			return GL_VERTEX_SHADER;
		}

		else if (!pType.compare("Fragment\r"))
		{
			return GL_FRAGMENT_SHADER;
		}

		else if (!pType.compare("Pixel\r"))
		{
			return GL_FRAGMENT_SHADER;
		}

		else if (!pType.compare("Compute\r"))
		{
			return GL_COMPUTE_SHADER;
		}

		else
		{
			return -1;
		}
	}

	unsigned int Shader::CompileShader(GLenum Type, const std::string& ShaderSource)
	{
		unsigned int Shader = glCreateShader(Type);
		const char* Source = ShaderSource.c_str();

		GLCall(glShaderSource(Shader, 1, &Source, NULL));
		GLCall(glCompileShader(Shader));

		int Succeed = 0;
		GLCall(glGetShaderiv(Shader, GL_COMPILE_STATUS, &Succeed));

		if (!Succeed)
		{
			char Message[510];
			GLCall(glGetShaderInfoLog)
			GLCall(glGetShaderInfoLog(Shader, 510, NULL, Message));

			Logger::CoreLogger->SetError(((Type == GL_VERTEX_SHADER) ? "Vertex:" : "Fragment:") + std::string(Message));

			GLCall(glDeleteShader(Shader));
			return 0;
		}
		return Shader;
	}




	void Shader::CreateShaderProgram()
	{

		//Create a new Program
		m_ProgramID = glCreateProgram();
		//Hold our shaders ID
		std::vector<int> Shaders;

		//we loop through Shaders in map
		for (auto &i : m_Shaders)
		{
			//Compile each shader
			int Shader = CompileShader(i.first, i.second);

			//Check if it compiled successfuly
			if (Shader == 0)
			{
				Logger::CoreLogger->SetWarning("Could not Compile Shader");
				return;
			}

			//Attach the shader to our program
			GLCall(glAttachShader(m_ProgramID, Shader));
			//Push the id of the shader to vector
			Shaders.push_back(Shader);
		}

		//Link the Shaders into Program & validate
		GLCall(glLinkProgram(m_ProgramID));
		GLCall(glValidateProgram(m_ProgramID));


		//Check if the linking was successful 
		int Succeed = 0;
		GLCall(glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Succeed));
		//Detach and delete the compiled shaders
		for (auto i : Shaders)
		{
			GLCall(glDetachShader(m_ProgramID, i));
			GLCall(glDeleteShader(i));
		}

		if (!Succeed)
		{
			char Message[510];
			GLCall(glGetProgramInfoLog(m_ProgramID, 510, NULL, Message));
			GLCall(glDeleteProgram(m_ProgramID));
			Logger::CoreLogger->SetError(std::string(Message));
			return;
		}

	}


	void Shader::ReloadShader()
	{
		//Delete the Old Shader
		Unbind();
		GLCall(glDeleteProgram(m_ProgramID));
		m_Shaders.clear();


		std::string Content = ReadFile(m_ShaderFilePath);
		Process(Content);
		CreateShaderProgram();
		Bind();
		Logger::CoreLogger->SetInfo("Shader Reloaded from " + std::string(m_ShaderFilePath));
	}

	int Shader::Process(const std::string& pShaderContent)
	{

		uint32 ContentSize = pShaderContent.size();
		std::string Line;
		std::string TypeToken = "Type";

		GLenum CurrentShaderType = 0;

		for (int i = 0; i <= ContentSize; ++i)
		{
			if (pShaderContent[i] == '\n' || i == ContentSize)
			{
				//if it was an empty line, we ignore it
				if (Line.size() == 1 && Line[0] == char(13))
				{
					Line.clear();
					continue;
				}

				//We ignore comments:
				if (Line.find("//") < Line.size())
				{
					Line.clear();
					continue;
				}

				//We Process the meta datas
				int Pos = Line.find("#");
				if (Pos < Line.size())
				{
					if (Line.substr(Pos + 1, TypeToken.length()) == TypeToken)
					{
						std::string T = Line.substr((Pos + TypeToken.length() + 2), Line.find(char(13)));
						
						CurrentShaderType = Shader::GetShaderEnum(T);
						if (CurrentShaderType == -1)
						{
							Logger::CoreLogger->SetError("Invalid Shader type:" + T);
							return 1;
						}

						Line.clear();
						continue;
					}
				}

				//at this point we have processed shader code
				if (CurrentShaderType!=0)
					m_Shaders[CurrentShaderType] += Line;
				Line.clear();
			}

			else
			{
				Line += pShaderContent[i];
			}
		}

		return 0;
	}

	bool Shader::DoesUniformExist(std::string pUniformName) const
	{
		if (m_ShaderUniforms.find(pUniformName) == m_ShaderUniforms.end())
			return false;
		return true;
	}

	int Shader::GetUniformLocation(std::string  Name) const
	{

		//Check if uniform existed:
		if (m_ShaderUniforms.find(Name) != m_ShaderUniforms.end())
		{
			return m_ShaderUniforms[Name];
		}

		int Loc = glGetUniformLocation(m_ProgramID, Name.c_str());

		if (Loc != -1)
		{
			m_ShaderUniforms[Name] = Loc;
			return Loc;
		}
		return -1;
	}


	int Shader::SetUniformF1(const char * p_UniformName, float p_Value) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			return 1;
		}
		GLCall(glUniform1f(Location, p_Value));
		return 0;
	}

	int Shader::SetUniformF2(const char * p_UniformName, float p_Value1, float p_Value2) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			return 1;
		}
		GLCall(glUniform2f(Location, p_Value1, p_Value2));
		return 0;
	}

	int Shader::SetUniformF3(const char * p_UniformName, float p_Value1, float p_Value2, float p_Value3) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			return 1;
		}
		GLCall(glUniform3f(Location, p_Value1, p_Value2, p_Value3));
		return 0;
	}

	int Shader::SetUniformF4(const char * p_UniformName, float p_Value1, float p_Value2, float p_Value3, float p_Value4) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			return 1;
		}
		GLCall(glUniform4f(Location, p_Value1, p_Value2, p_Value3, p_Value4));
		return 0;
	}

	TX_API int Shader::SetUniformMat4(const char * p_UniformName, glm::mat4& p_Value) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			return 1;
		}
		GLCall(glUniformMatrix4fv(Location, 1, GL_FALSE, glm::value_ptr(p_Value)));
	}

	int Shader::SetUniformI1(const char * p_UniformName, int p_Value) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			return 1;
		}
		GLCall(glUniform1i(Location, p_Value));
		return 0;
	}


	const std::string & Shader::GetShaderSource(const char* Type)
	{


		return "Not Found";
	}



};