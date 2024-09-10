#Shader Vertex

#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 m_Color;

out vec4 Our_Color;

uniform float Scale = 1;
uniform float u_Color = 1;

void main()
{
	gl_Position	 = vec4(aPos.x*Scale, aPos.y*Scale, 0.0f*Scale, 1.0f);

	Our_Color = vec4(m_Color.x * u_Color, m_Color.y*u_Color, m_Color.z*u_Color, 1.0f);

}

#End


#Shader Fragment

#version 330 core
out vec4 FragColor;
in vec4 Our_Color;


void main()
{
	FragColor = Our_Color;
}

#End