
#Type:Vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 m_TexCoord;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

out vec3 Normal;
out vec2 TextureCoords;
out vec3 FragmentPos;

void main()
{
	gl_Position	 = Projection * View * Model * vec4(aPos, 1.0f);
	TextureCoords = m_TexCoord;
	Normal = vec3(Model * vec4(aNormal, 0.0f));
	//Normal = aNormal;
	FragmentPos = vec3(Model * vec4(aPos, 1.0f));
};


#Type:Fragment
#version 330 core


struct Meterial
{
	vec3 Color;
	sampler2D Texture;
	float Shininess;
};

struct Light
{
    vec3 Position;
    vec3 Color;

	float Constant;
	float Linear;
	float Quadratic;
};

uniform Meterial meterial;
uniform Light light;

out vec4 FragColor;


in vec3 Normal;
in vec3 FragmentPos;
in vec2 TextureCoords;
uniform vec3 ViewPosition;


void main()
{

    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * light.Color;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.Position - FragmentPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.Color;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(ViewPosition - FragmentPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), meterial.Shininess);
    vec3 specular = specularStrength * spec * light.Color;  
        

	float Distance = length(light.Position - FragmentPos);
	float attenuation = 1.0 / (light.Constant + light.Linear * Distance + light.Quadratic * (Distance * Distance));  

	ambient *= attenuation ;
	diffuse *= attenuation ;
	specular *= attenuation ;

    vec3 result = (ambient + diffuse + specular) * meterial.Color;
    FragColor = vec4(result, 1.0);  
};
