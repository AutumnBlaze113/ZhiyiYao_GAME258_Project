#include "Mesh.h"


Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_)
	:VAO(0), VBO(0),  
	shaderProgram(0), viewLoc(0), projectionLoc(0), textureID(0), textureLoc(0), 
	viewPosition(0), 
	LightPos(0), ambient(0), diffuse(0), specular(0), lightColour(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera, std::vector<glm::mat4> instances_)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPerspective()));

	glUniform3fv(viewPosition, 1, glm::value_ptr(camera->GetPosition()));
	glUniform3fv(LightPos, 1, glm::value_ptr(camera->GetLight().position));
	glUniform1f(ambient, camera->GetLight().ambient);
	glUniform1f(diffuse, camera->GetLight().diffuse);
	glUniform1f(specular, camera->GetLight().specular);
	glUniform3fv(lightColour, 1, glm::value_ptr(camera->GetLight().colour));

	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	for (unsigned int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}
	// array thing is ready, unchangeable after this line

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	// position, 2d 3d? 

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	//COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");
	viewPosition = glGetUniformLocation(shaderProgram, "viewPosition");//
	LightPos = glGetUniformLocation(shaderProgram, "light.lightPos");
	ambient = glGetUniformLocation(shaderProgram, "light.ambient");
	diffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	specular = glGetUniformLocation(shaderProgram, "light.specular");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightColour");
	
}
