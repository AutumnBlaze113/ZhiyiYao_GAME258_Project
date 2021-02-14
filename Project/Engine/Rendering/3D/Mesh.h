#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoordinates;
	glm::vec3 colour;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>& vertexList_);
	~Mesh();

	void Render();

private:
	void GenerateBuffers();
	GLuint VAO, VBO;
	// VAO: Vertex Array Object, states to the GPU how we store our vertex data
	// VBO: Vertex Buffer Objects, provides the methods to push data to the GPU
	std::vector<Vertex> vertexList;
};

#endif // !MESH_H

