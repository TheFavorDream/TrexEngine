//Vertex Shader
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 m_Color;
out vec4 Our_Color;
uniform float u_Scale = 1;
uniform float u_R = 1;
uniform float u_G = 1;
uniform float u_B = 1;
void main()
{
	gl_Position	 = vec4(aPos.x*u_Scale, aPos.y*u_Scale, 0.0f, 1.0f);
	Our_Color = vec4(m_Color.x*u_R, m_Color.y*u_G, m_Color.z*u_B, 1.0f);
};


//Fragment Shader
#version 330 core
out vec4 FragColor;
in vec4 Our_Color;

void main()
{
	FragColor = Our_Color;
};