#include "../Include/Renderer/OpenGL/Shader.h"


namespace TrexEngine
{

	Shader::Shader(const char* ShaderFilePath)
	{

		if (ReadShadersFromSourceFile(ShaderFilePath) > 0)
		{
			return;
		}
	}

	Shader::~Shader()
	{
	
		GLCall(glDeleteProgram(ProgramID));

		int State = 0;

		GLCall(glGetProgramiv(ProgramID, GL_DELETE_STATUS, &State));

		if (State == GL_TRUE)
		{
			Logger::CoreLogger->SetWarning("Shader Program is seted to deletion");
		}
		else
		{
			Logger::CoreLogger->SetWarning("Shader Program is NOT seted to deletion");
		}

	}


	void Shader::Bind()
	{
		GLCall(glUseProgram(ProgramID));
	}


	void Shader::Unbind()
	{
		GLCall(glUseProgram(0));
	}


	int Shader::ReadShadersFromSourceFile(const char* FilePath)
	{

		std::ifstream SourceFile(FilePath);

		if (SourceFile.fail())
		{
			Logger::CoreLogger->SetError("Cannot Open the Shader Source File");
			return 1;
		}


		std::string line;
		std::string* Current = NULL;
		bool Reading = false;

		while (!SourceFile.eof())
		{
			std::getline(SourceFile, line, '\n');

			if (line == "#End")
			{
				Reading = false;
				Current = NULL;
			}

			if (Reading)
			{
				(*Current) += (line + "\n");
			}


			if (line == "#Shader Vertex")
			{
				Reading = true;
				Current = &VertexShaderSource;
			}

			else if (line == "#Shader Fragment")
			{
				Reading = true;
				Current = &FragmentShaderSource;
			}

		}

		SourceFile.close();

		return 0;
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

		Bind();
	}

	int Shader::SetUniformF(const char * p_UniformName, float p_Value)
	{
		int Location = glGetUniformLocation(ProgramID, p_UniformName);

		if (Location == -1)
		{
			Logger::CoreLogger->SetError("Cannot Find the Location of the uniform");
			return 1;
		}

		GLCall(glUniform1f(Location, p_Value));
		return 0;
	}

	int Shader::SetUniformI(const char * p_UniformName, int p_Value)
	{
		int Location = glGetUniformLocation(ProgramID, p_UniformName);

		if (Location == -1)
		{
			Logger::CoreLogger->SetError("Cannot Find the Location of the uniform");
			return 1;
		}

		GLCall(glUniform1i(Location, p_Value));
	}



};