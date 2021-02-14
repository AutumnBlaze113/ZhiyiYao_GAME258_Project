#include "GameScene.h"

GameScene::GameScene() :shape(nullptr)
{
}

GameScene::~GameScene()
{
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	Debug::Info("Game Scene created successfully", "GameScene.cpp ", __LINE__);
	
	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(6);

	// 1st triangle
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	// 2nd triangle
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	
	Model* model = new Model();
	model->AddMesh(new Mesh(vertexList));
	shape = new GameObject(model);

	return true;
}

void GameScene::Update(const float deltaTime_)
{
	//std::cout << "GameScene:  " << deltaTime_ << "\n" <<std::endl;// print out time
}       

void GameScene::Render()
{
	shape->Render();
}
