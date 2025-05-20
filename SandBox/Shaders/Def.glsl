
#Type:Vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 m_TexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec3 Normal;
out vec2 TexCoord;
out vec3 FragmentPos;

void main()
{
	gl_Position	 = Projection * View * Model * vec4(aPos, 1.0f);
	TexCoord = m_TexCoord;
	Normal = aNormal;
	FragmentPos = vec3(Model * vec4(aPos, 1.0f));
};


#Type:Fragment
#version 330 core


struct Meterial
{
	sampler2D Diffuse;
	sampler2D Specular;
	float Shininess;
};

struct Light
{

    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

};

uniform Meterial meterial;
uniform Light light;

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragmentPos;

uniform vec3 ViewPosition;


void main()
{


	//Diffuse Calculation
	vec3 Norm = normalize(Normal);
	vec3 LightDir = normalize(light.Position - FragmentPos);
	float Diff = max(dot(Norm, LightDir), 0.0);



	vec3 ViewDir = normalize(ViewPosition - FragmentPos);
	vec3 Reflect = reflect(-ViewDir, Norm);
    float spec = pow(max(dot(ViewDir, Reflect), 0.0), meterial.Shininess);


	vec3 ambient  = light.Ambient  * texture(meterial.Diffuse, TexCoord).rgb;
	vec3 diffuse  = light.Diffuse  * Diff * texture(meterial.Diffuse, TexCoord).rgb;  
	vec3 specular = light.Specular * spec * texture(meterial.Specular, TexCoord).rgb;

	vec3 Res = ambient + diffuse + specular;
	FragColor = vec4(Res, 1.0);   
};
