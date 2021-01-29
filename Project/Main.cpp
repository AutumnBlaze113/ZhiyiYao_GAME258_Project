#include "Engine/Core/CoreEngine.h"

CoreEngine* engine;

int main(int argc, char* argv[]) {


	//engine = new CoreEngine;
	//if (!engine->OnCreate("Demo", 800, 600)){
	if (!CoreEngine::GetInstance()->OnCreate("ZhiyiYao GAME258", 800, 600)) {
		std::cout << "Engine failed to initialize" << std::endl;
		return 0;
	}


	//engine->Run();
	CoreEngine::GetInstance()->Run();
	//delete engine;
	//engine = nullptr;


	return 0;
}