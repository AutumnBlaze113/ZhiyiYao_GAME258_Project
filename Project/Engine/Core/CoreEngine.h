#ifndef COREENGINE_H
#define COREENGINE_H


#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"
#include<memory>//for smart pointers

class CoreEngine
{
public:// Singleton Engine
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;
	//Disable the creation of copy or move constructors
	//If anyone wants to create a move or a copy construction of the class, he will get an error

	// call it when you want to get access to anything public 
	static CoreEngine* GetInstance();

	//Create a window
	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();

	bool GetIsRunning() const;
	int GetCurrentScene() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);

private:
	CoreEngine();
	~CoreEngine(); 
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<CoreEngine> engineInstance;//holds a pointer to CoreEngine class
	friend std::default_delete<CoreEngine>;// friends can see private things
	
	//When the pointer goes out of scope or the program ends, the pointer will delete itself automatically


	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;
};



#endif

