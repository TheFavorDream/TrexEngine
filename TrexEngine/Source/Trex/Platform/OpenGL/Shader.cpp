#include "Shader.h"


namespace TrexEngine
{

	Shader::Shader()
	{
		Shader_Ref = this;
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

	void Shader::CreateShaderProgram(const std::string& VertexShader, const std::string& FragmentShader)
	{
		unsigned int VS = CompileShader(GL_VERTEX_SHADER, VertexShader);
		unsigned int FS = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);

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

	int Shader::SetUniformF(const char * p_UniformName, float p_Value) const
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

	int Shader::SetUniformI(const char * p_UniformName, int p_Value) const
	{
		int Location = glGetUniformLocation(ProgramID, p_UniformName);

		if (Location == -1)
		{
			Logger::CoreLogger->SetError("Cannot Find the Location of the uniform");
			return 1;
		}

		GLCall(glUniform1i(Location, p_Value));

		return 0;
	}

	TX_API int Shader::SetUniformF3(const char * p_UniformName, int p_Value1, int p_Value2, int p_Value3) const
	{
		int Location = glGetUniformLocation(ProgramID, p_UniformName);

		if (Location == -1)
		{
			Logger::CoreLogger->SetError("Cannot Find the Location of the uniform");
			return 1;
		}

		GLCall(glUniform3f(Location, p_Value1, p_Value2, p_Value3));
	}



};