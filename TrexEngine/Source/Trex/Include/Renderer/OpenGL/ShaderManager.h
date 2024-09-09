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

		TX_API Shader(const char* ShaderFilePath = 0);
		TX_API ~Shader();

		TX_API void Bind();
		TX_API void Unbind();

		void CreateShaderProgram();

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