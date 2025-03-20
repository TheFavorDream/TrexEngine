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
	
		enum GLSLDataTypes {FLOAT=1, INT, CHAR, SAMPLER2D, SAMPLER3D};

		struct Uniform
		{
			uint16 Type;
			std::string Name;
			float Data = 0.0f;
			bool Changed = false;

			inline bool IsChanged()
			{ 
				bool t = Changed;
				Changed = false;
				return t; 
			}
			void SetData(float pData) 
			{ 
				Data = pData; 
				Changed = true;
			}
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
		TX_API Uniform* GetUniform(std::string pName);

		TX_API void ReloadShader();

		TX_API bool DoesUniformExist(const char* p_UniformName) const;
		TX_API int GetUniformLocation(std::string Name)    const;

		TX_API int SetUniformF1(const char* p_UniformName, float p_Value) const;
		TX_API int SetUniformF2(const char* p_UniformName, float p_Value1, float p_Value2)   const;
		TX_API int SetUniformF3(const char* p_UniformName, float p_Value1, float p_Value2, float p_Value3)   const;
		TX_API int SetUniformF4(const char* p_UniformName, float p_Value1, float p_Value2, float p_Value3, float p_Value4)   const;

		TX_API int SetUniformI1(const char* p_UniformName, int p_Value)   const;

		TX_API const std::string& GetShaderSource(const char* Type);
		TX_API const std::vector<Uniform>& GetShaderUniformList();
	private:
		TX_API unsigned int CompileShader(unsigned int Type, const std::string& ShaderSource);

	private:

		GLuint ProgramID = 0;
		const char* ShaderFilePath = 0;
		std::string VertexShaderSource = "";
		std::string FragmentShaderSource = "";

		mutable std::unordered_map<std::string, unsigned int> m_ShaderUniforms;
		std::vector<Uniform> m_UniformList;
	};


};