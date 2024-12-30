#pragma once


#include "../Core/Core.h"
#include "../3rdparty/GL/glew.h"
#include "../Debug/Log.h"
#include <string>
#include <fstream>
#include <iostream>

namespace TrexEngine
{

	class Shader
	{
	public:
	
		enum GLSLDataTypes {FLOAT=1, INT, CHAR, SAMPLER2D, SAMPLER3D};

		struct Uniform
		{
			uint16 Type;
			std::string Name;
		};

	public:

		TX_API Shader(const char* p_FilePath);

		TX_API ~Shader();


		TX_API void Bind();
		TX_API void Unbind();

		TX_API void ReadShaderFile(const char* p_FileFile);
		TX_API void CreateShaderProgram();

		//This method gets an uniform definition as a string and convertes it to "Uniform" and stroes it in m_UniformList
		TX_API int CreateNewUniform(const std::string& pLine);

		TX_API void ReloadShader();

		TX_API int SetUniformF(const char* p_UniformName, float p_Value) const;
		TX_API int SetUniformI(const char* p_UniformName, int p_Value)   const;
		TX_API int SetUniformF3(const char* p_UniformName, int p_Value1, int p_Value2, int p_Value3)   const;

		TX_API const std::string& GetShaderSource(const char* Type);
		TX_API const std::vector<Uniform>& GetShaderUniformList();
	private:
		TX_API unsigned int CompileShader(unsigned int Type, const std::string& ShaderSource);

	private:


		GLuint ProgramID = 0;
		const char* ShaderFilePath = 0;
		std::string VertexShaderSource = "";
		std::string FragmentShaderSource = "";
		std::vector<Uniform> m_UniformList;
	};


};