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
"uniform float Scale = 1;\n"
"uniform float u_Color = 1;\n"
"void main()\n"
"{\n"
"	gl_Position	 = vec4(aPos.x*Scale, aPos.y*Scale, 0.0f*Scale, 1.0f);\n"
"	Our_Color = vec4(m_Color.x * u_Color, m_Color.y*u_Color, m_Color.z*u_Color, 1.0f);\n"
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

		Shader();
		~Shader();

		void Bind();
		void Unbind();

		void CreateShaderProgram(const std::string& VertexShader, const std::string& FragmentShader);

		TX_API int SetUniformF(const char* p_UniformName, float p_Value) const;
		TX_API int SetUniformI(const char* p_UniformName, int p_Value)   const;


	private:
		unsigned int CompileShader(unsigned int Type, const std::string& ShaderSource);

	private:

		unsigned int ShaderID = 0;

		unsigned int ProgramID = 0;
		const char* ShaderFilePath = 0;
	};

};