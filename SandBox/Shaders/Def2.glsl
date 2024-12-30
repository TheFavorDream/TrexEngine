//Vertex Shader
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 m_Color;
out vec4 Our_Color;
uniform float Opacity = 1.0f;
void main()
{
	gl_Position	 = vec4(aPos.x*0.5f, aPos.y*0.5f, 0.0f, 1.0f);
	Our_Color = vec4(m_Color.x, m_Color.y, m_Color.z, 1.0f) * Opacity;
};


//Fragment Shader
#version 330 core
out vec4 FragColor;
in vec4 Our_Color;

void main()
{
	FragColor = Our_Color;
};