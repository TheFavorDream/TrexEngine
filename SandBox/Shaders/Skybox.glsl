//Vertex Shader

#Type:Vertex
#version 330

layout (location=0) in vec3 Position;

out vec3 TexCoords;

uniform mat4 View_Projection;


void main()
{
    TexCoords = Position;
    vec4 pos = View_Projection * vec4(Position, 1.0);
    gl_Position = pos.xyww;
}  


//Fragment Shader
#Type:Fragment

#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    vec4 Tex = texture(skybox, TexCoords);
	FragColor = Tex;
}