#pragma once
#include "../Core/Core.h"
#include "../3rdparty/GL/glew.h"
#include "../Debug/Log.h"
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>


namespace TrexEngine
{

	class Shader
	{
	public:

		TX_API Shader(const std::string& pFilePath);
		TX_API Shader(const std::string& pVertexShader, const std::string& pFragmentShader);

		TX_API ~Shader();


		TX_API void Bind();
		TX_API void Unbind();

		TX_API const std::string ReadFile(const std::string& pFilePath);

		TX_API void CreateShaderProgram();
		TX_API void ReloadShader();

		TX_API int Process(const std::string& pShaderContent);

		TX_API bool DoesUniformExist(std::string pUniformName) const;
		TX_API int GetUniformLocation(std::string Name)    const;

		TX_API int SetUniformF1(const char* p_UniformName, float p_Value) const;
		TX_API int SetUniformF2(const char* p_UniformName, float p_Value1, float p_Value2)   const;
		TX_API int SetUniformF3(const char* p_UniformName, float p_Value1, float p_Value2, float p_Value3)   const;
		TX_API int SetUniformF4(const char* p_UniformName, float p_Value1, float p_Value2, float p_Value3, float p_Value4)   const;

		TX_API int SetUniformI1(const char* p_UniformName, int p_Value)   const;

		TX_API const std::string& GetShaderSource(const char* Type);


	public:
		static GLenum GetShaderEnum(const std::string& pType);
	private:
		TX_API unsigned int CompileShader(GLenum Type, const std::string& ShaderSource);

	private:

		GLuint m_ProgramID = 0;
		std::string m_ShaderFilePath;
		std::unordered_map<GLenum, std::string> m_Shaders;
		mutable std::unordered_map<std::string, unsigned int> m_ShaderUniforms;
	};


};