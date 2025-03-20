//Vertex Shader
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 m_Color;
out vec4 Our_Color;


uniform float u_R = 1.0f;
uniform float u_G = 1.0f;
uniform float u_B = 1.0f;

void main()
{
	gl_Position	 = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
	Our_Color = vec4(u_R, u_G, u_B, 1.0f);
};


//Fragment Shader
#version 330 core
out vec4 FragColor;
in vec4 Our_Color;

void main()
{
	FragColor = Our_Color;
};