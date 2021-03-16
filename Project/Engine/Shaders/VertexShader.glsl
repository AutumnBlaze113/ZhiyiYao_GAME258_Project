#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 colour;

out vec3 Normal;
out vec2 TexCoords;
out vec3 Colour;
out vec3 FragPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){

	Normal = mat3(transpose(inverse(model))) * normal; 
	FragPosition = vec3(model * vec4(position, 1.0f));
	gl_Position = projection * view * model * vec4(position, 1.0f); //main role 
	Colour = colour;
	TexCoords = texCoords;

	//make this Normal out variable equal the 
	//inverse transpose of the model matrix multiplied by the normal data from the layout
	//inverse and transpose
	

}