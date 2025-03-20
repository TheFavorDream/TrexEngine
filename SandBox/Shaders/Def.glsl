//Vertex Shader
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 m_Color;
layout(location = 2) in vec2 m_TexCoord;

out vec4 Our_Color;
out vec2 TexCoord;

void main()
{
	gl_Position	 = vec4(aPos, 0.0f, 1.0f);
	TexCoord = m_TexCoord;
	Our_Color = vec4(m_Color, 1.0f);
};


//Fragment Shader
#version 330 core
out vec4 FragColor;

in vec4 Our_Color;
in vec2 TexCoord;

uniform sampler2D Tex;

void main()
{
	FragColor = texture(Tex, TexCoord);
};