#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	//std::cout << "start scene" << std::endl;
	Debug::Info("Start Scene created successfully", "StartScene.cpp ", __LINE__);
	return true;
}

void StartScene::Update(const float deltaTime_)
{
	CoreEngine::GetInstance()->SetCurrentScene(1);
}

void StartScene::Render()// only for drawing !!!
{
	//CoreEngine::GetInstance()->SetCurrentScene(1); // switch to GameScene
}
