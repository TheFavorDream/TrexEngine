
#Type:Vertex
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 m_Color;
layout(location = 2) in vec2 m_TexCoord;

out vec4 Our_Color;
out vec2 TexCoord;

void main()
{
	gl_Position	 = vec4(aPos.x,aPos.y, 0.0f, 1.0f);
	TexCoord = m_TexCoord;
	Our_Color = vec4(m_Color, 1.0f);
};


#Type:Fragment
#version 330 core
out vec4 FragColor;

in vec4 Our_Color;
in vec2 TexCoord;

uniform sampler2D Tex;

void main()
{
	FragColor = mix(texture(Tex, TexCoord), vec4(0.2f, 0.5f, 0.1f, 1.0f), 0.1f);
};
