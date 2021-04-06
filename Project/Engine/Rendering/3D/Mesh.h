#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
}; // don't forget the ;

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<unsigned int> meshIndices;
	Material material;
	//GLuint textureID;
};

class Mesh
{
public:
	Mesh(SubMesh& subMesh_, GLuint shaderProgram_);
	~Mesh();

	void Render(Camera* camera_, std::vector<glm::mat4> instances_);

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	// VAO: Vertex Array Object, states to the GPU how we store our vertex data
	// VBO: Vertex Buffer Objects, provides the methods to push data to the GPU
	SubMesh subMesh;
	GLuint shaderProgram;
	GLuint textureID;
	GLuint modelLoc, viewLoc, projectionLoc, textureLoc;
	GLuint viewPosition;
	GLuint LightPos, ambient, diffuse, specular, lightColour;
	GLuint diffuseMap, shininess, transparency, Mambient, Mdiffuse, Mspecular;
};

#endif // !MESH_H

