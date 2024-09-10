#pragma once


#include "../../Core.h"
#include "../../GL/glew.h"
#include "../../Log.h"

#include <iostream>

namespace TrexEngine
{

	class Shader
	{

	public:

		Shader(const char* ShaderFilePath = 0);
		~Shader();

		void Bind();
		void Unbind();

		void CreateShaderProgram();

		TX_API int SetUniformF(const char* p_UniformName, float p_Value);
		TX_API int SetUniformI(const char* p_UniformName, int p_Value);


	private:
		int ReadShadersFromSourceFile(const char* FilePath);
		unsigned int CompileShader(unsigned int Type, const std::string& ShaderSource);

	private:

		std::string VertexShaderSource;
		std::string FragmentShaderSource;

		unsigned int ShaderID = 0;

		unsigned int ProgramID = 0;
		const char* ShaderFilePath = 0;
	};

};