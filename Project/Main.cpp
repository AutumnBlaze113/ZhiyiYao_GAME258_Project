#include "Engine/Core/CoreEngine.h"

CoreEngine* engine;

int main(int argc, char* argv[]) {


	//engine = new CoreEngine;
	if (!engine->OnCreate("ZhiyiYao GAME258", 800, 600)) {
		//delete engine;
		//engine = nullptr;
		return 0;
	}


	//engine->Run();
	CoreEngine::GetInstance()->Run();
	//delete engine;
	//engine = nullptr;


	return 0;
}