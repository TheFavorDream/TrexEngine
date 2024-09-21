#pragma once


#include "../../Core.h"
#include "../../GL/glew.h"
#include "../../Log.h"




#include <string>

static std::string VertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec2 aPos;\n"
"layout(location = 1) in vec3 m_Color;\n"
"out vec4 Our_Color;\n"
"uniform float ScaleY = 1;\n"
"uniform float ScaleX = 1;\n"
"uniform float u_A = 1;\n"
"uniform float u_R = 1;\n"
"uniform float u_G = 1;\n"
"uniform float u_B = 1;\n"
"void main()\n"
"{\n"
"	gl_Position	 = vec4(aPos.x*ScaleX, aPos.y*ScaleY, 0.0f, 1.0f);\n"
"	Our_Color = vec4(u_R*u_A ,u_G*u_A, u_B*u_A, 1.0f);\n"
"}\n";



static std::string FragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 Our_Color;\n"

"void main()\n"
"{\n"
"FragColor = Our_Color;\n"
"}\n";


#include <iostream>

namespace TrexEngine
{

	class Shader
	{

	public:

		TX_API Shader();

		TX_API ~Shader();

		TX_API void Bind();
		TX_API void Unbind();

		TX_API void CreateShaderProgram(const std::string& VertexShader, const std::string& FragmentShader);

		TX_API int SetUniformF(const char* p_UniformName, float p_Value) const;
		TX_API int SetUniformI(const char* p_UniformName, int p_Value)   const;
		TX_API int SetUniformF3(const char* p_UniformName, int p_Value1, int p_Value2, int p_Value3)   const;

	private:
		TX_API unsigned int CompileShader(unsigned int Type, const std::string& ShaderSource);

	private:

		unsigned int ShaderID = 0;

		unsigned int ProgramID = 0;
		const char* ShaderFilePath = 0;
	};

	static Shader* Shader_Ref = NULL;

};