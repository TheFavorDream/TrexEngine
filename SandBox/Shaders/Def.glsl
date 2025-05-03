
#Type:Vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 m_TexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec2 TexCoord;

void main()
{
	gl_Position	 = Projection * View * Model * vec4(aPos, 1.0f);
	TexCoord = m_TexCoord;
};


#Type:Fragment
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D Tex;

void main()
{
	FragColor = mix(texture(Tex, TexCoord), vec4(0.5f, 0.5f, 0.1f, 1.0f), 0.0f);
};
