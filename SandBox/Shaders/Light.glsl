//Vertex Shader
#Type:Vertex
#version 330 core
layout (location = 0) in vec3 aPos;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{


    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
}  

//Fragment Shader
#Type:Fragment
#version 330 core
out vec4 FragColor;
uniform vec3 LightColor;

void main()
{             

    FragColor = vec4(LightColor, 1.0f);
}