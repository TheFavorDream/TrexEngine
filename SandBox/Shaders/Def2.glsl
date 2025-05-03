//Vertex Shader

#Type:Vertex
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 m_Color;
layout(location = 2) in vec2 m_TexCoords;

out vec4 Our_Color;
out vec2 out_TexCoords;

uniform float u_ = 1.0f;
uniform float u_G = 1.0f;
uniform float u_B = 1.0f;

void main()
{
	out_TexCoords = m_TexCoords;
	gl_Position	 = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
	Our_Color = vec4(aPos, 0.0f, 1.0f);
};


//Fragment Shader
#Type:Fragment
#version 330 core

out vec4 FragColor;
in vec4 Our_Color;
in vec2 out_TexCoords;

uniform sampler2D Tex;

void main()
{
	FragColor = mix(texture(Tex, out_TexCoords), Our_Color, 0.5f);
};