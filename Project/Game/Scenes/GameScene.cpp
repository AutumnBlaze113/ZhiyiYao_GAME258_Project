#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::OnCreate()
{
	Debug::Info("Game Scene created successfully", "GameScene.cpp ", __LINE__);
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	std::cout << "GameScene:  [" << deltaTime_ << "]" <<std::endl;// print out time
}       

void GameScene::Render()
{
}
