#version 450 core

struct Light{
	vec3 lightPos;
	float ambient; 
	float diffuse;
	float specular;
	vec3 lightColour;
}; 

struct Material{
	sampler2D diffuseMap; //newmtl

	float shininess; //Ns
	float transparency; //d

	vec3 ambient; //Ka
	vec3 diffuse; //Kd
	vec3 specular; // Ks

};

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

uniform vec3 viewPosition;
uniform Light light;
uniform Material material;

out vec4 fColour;



void main(){
	//fColour = texture(inputTexture, TexCoords);

	//Ambient
	vec3 ambient = light.ambient * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.lightPos - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//Specular
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColour;

	vec3 result = ambient + diffuse + specular;
	fColour = vec4(result, material.transparency);
}