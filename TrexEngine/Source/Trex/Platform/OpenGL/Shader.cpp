#include "Shader.h"


namespace TrexEngine
{

	Shader::Shader(const char* p_FilePath)
	{
		ShaderFilePath = p_FilePath;
		ReadShaderFile(p_FilePath);
		CreateShaderProgram();
	}


	Shader::~Shader()
	{
		GLCall(glDeleteProgram(ProgramID));
	}


	void Shader::Bind()
	{
		GLCall(glUseProgram(ProgramID));
	}


	void Shader::Unbind()
	{
		GLCall(glUseProgram(0));
	}


	TX_API void Shader::ReadShaderFile(const char* p_FileFile)
	{
		VertexShaderSource = "";
		FragmentShaderSource = "";

		std::ifstream SourceFile(p_FileFile, std::ios::in);

		if (SourceFile.fail())
		{
			Logger::CoreLogger->SetError("Shader File at Path :" + std::string(p_FileFile) + " Does Not Exist");
			return;
		}


		bool IsReading = false;
		std::string* Current;
		std::string Line;

		while (!SourceFile.eof())
		{
			std::getline(SourceFile, Line, '\n');

			if (Line == "//Vertex Shader")
			{
				IsReading = true;
				Current = &VertexShaderSource;
				Line = "";
			}

			else if (Line == "//Fragment Shader")
			{
				IsReading = true;
				Current = &FragmentShaderSource;
				Line = "";
			}

			if (IsReading)
			{
				(*Current) += Line + "\n";
				

				if (Line.length() > 8 && Line.substr(0, 7) == "uniform")
				{
					CreateNewUniform(Line);
				}
				

			}
		}

		SourceFile.close();
	}

	unsigned int Shader::CompileShader(unsigned int Type, const std::string& ShaderSource)
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


	//Temp
	TX_API Shader::Uniform* Shader::GetUniform(std::string pName)
	{
		for (auto &i : m_UniformList)
		{
			if (i.Name == pName)
			{
				return &i;
			}
		}
		return NULL;
	}

	void Shader::CreateShaderProgram()
	{
		unsigned int VS = CompileShader(GL_VERTEX_SHADER, VertexShaderSource);
		unsigned int FS = CompileShader(GL_FRAGMENT_SHADER, FragmentShaderSource);

		ProgramID = glCreateProgram();
		GLCall(glAttachShader(ProgramID, VS));
		GLCall(glAttachShader(ProgramID, FS));

		GLCall(glLinkProgram(ProgramID));

		GLCall(glValidateProgram(ProgramID));

		int Succeed = 0;

		GLCall(glGetProgramiv(ProgramID, GL_LINK_STATUS, &Succeed));

		if (!Succeed)
		{

			char Message[510];
			GLCall(glGetProgramInfoLog(ProgramID, 510, NULL, Message));
			GLCall(glDeleteProgram(ProgramID));
			Logger::CoreLogger->SetError(std::string(Message));
			return;
		}

		GLCall(glDetachShader(ProgramID, VS));
		GLCall(glDetachShader(ProgramID, FS));

		GLCall(glDeleteShader(VS));
		GLCall(glDeleteShader(FS));


	}

	TX_API int Shader::CreateNewUniform(const std::string & pLine)
	{

		std::string tmp;
		Uniform New;

		for (int i = 8; i < pLine.length() ; i++)
		{
			char c = pLine[i];

			if (c == '=' || c== ';')
			{ 
				break;
			}

			else if (c != ' ')
			{
				tmp += c;
			}

			else
			{
				if (tmp == "float")
				{
					New.Type = FLOAT;
				}

				else if (tmp == "int")
				{
					New.Type = INT;
				}

				else
				{
					New.Name = tmp;
				}
				
				tmp = "";
			}

		}

		m_UniformList.push_back(New);

		return 0;
	}

	TX_API void Shader::ReloadShader()
	{
		//Delete the Old Shader
		Unbind();
		GLCall(glDeleteProgram(ProgramID));
		m_UniformList.clear();

		ReadShaderFile(ShaderFilePath);
		CreateShaderProgram();
		
		Logger::CoreLogger->SetInfo("Shader Reloaded from " + std::string(ShaderFilePath));
	}

	TX_API bool Shader::DoesUniformExist(const char * p_UniformName) const
	{
		for (auto &i : m_UniformList)
		{
			if (i.Name == p_UniformName)
			{
				return true;
			}
		}

		return false;
	}

	TX_API int Shader::GetUniformLocation(std::string  Name) const
	{

		//Check if uniform existed:
		if (m_ShaderUniforms.find(Name) != m_ShaderUniforms.end())
		{
			return m_ShaderUniforms[Name];
		}

		int Loc = glGetUniformLocation(ProgramID, Name.c_str());

		if (Loc != -1)
		{
			m_ShaderUniforms[Name] = Loc;
			return Loc;
		}
		return -1;
	}


	TX_API int Shader::SetUniformF1(const char * p_UniformName, float p_Value) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			Logger::CoreLogger->SetError("Cannot Find the Location of the " + std::string(p_UniformName) + " uniform");
			return 1;
		}
		GLCall(glUniform1f(Location, p_Value));
		return 0;
	}

	TX_API int Shader::SetUniformF2(const char * p_UniformName, float p_Value1, float p_Value2) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			Logger::CoreLogger->SetError("Cannot Find the Location of the " + std::string(p_UniformName) + " uniform");
			return 1;
		}
		GLCall(glUniform2f(Location, p_Value1, p_Value2));
		return 0;
	}

	TX_API int Shader::SetUniformF3(const char * p_UniformName, float p_Value1, float p_Value2, float p_Value3) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			Logger::CoreLogger->SetError("Cannot Find the Location of the " + std::string(p_UniformName) + " uniform");
			return 1;
		}
		GLCall(glUniform3f(Location, p_Value1, p_Value2, p_Value3));
		return 0;
	}

	TX_API int Shader::SetUniformF4(const char * p_UniformName, float p_Value1, float p_Value2, float p_Value3, float p_Value4) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			Logger::CoreLogger->SetError("Cannot Find the Location of the " + std::string(p_UniformName) + " uniform");
			return 1;
		}
		GLCall(glUniform4f(Location, p_Value1, p_Value2, p_Value3, p_Value4));
		return 0;
	}

	TX_API int Shader::SetUniformI1(const char * p_UniformName, int p_Value) const
	{
		int Location = GetUniformLocation(p_UniformName);
		if (Location == -1)
		{
			Logger::CoreLogger->SetError("Cannot Find the Location of the " + std::string(p_UniformName) + " uniform");
			return 1;
		}
		GLCall(glUniform1i(Location, p_Value));
		return 0;
	}


	TX_API const std::string & Shader::GetShaderSource(const char* Type)
	{
		if (Type == "Vertex Shader")
		{
			return VertexShaderSource;
		}

		else if (Type == "Fragment")
		{
			return FragmentShaderSource;
		}

		return "Not Found";
	}

	TX_API const std::vector<TrexEngine::Shader::Uniform>& Shader::GetShaderUniformList()
	{
		return m_UniformList;
	}



};