#include "Window.h"
#include "Debug.h"

Window::Window() : window(nullptr), context(nullptr)
{
	window = nullptr;
	context = nullptr;
}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {//initalize SDL (video)
		//std::cout << "Fail to initialize SDL! " << std::endl;
		Debug::FatalError("Fail to initialize SDL! ", "Window.cpp ", __LINE__);
		return false;
	}
	//this->width = width_;
	//this->height = height_;
	width = width_;
	height = height_;

	SetPreAttributes();

	window = SDL_CreateWindow(name_.c_str(),
		SDL_WINDOWPOS_CENTERED,// x
		SDL_WINDOWPOS_CENTERED,// y 
		//(it will appear at the center of the screen)
		width,
		height,
		SDL_WINDOW_OPENGL);
		//declare there will be openGL

	if (!window) {//(window == nullptr)
		//std::cout << "Failed to create window! " << std::endl;
		Debug::FatalError("Failed to create window! ", "Window.cpp ", __LINE__);
		return false;
	}

	context = SDL_GL_CreateContext(window);
	SetPostAttributes();

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		//std::cout << "Fail to intialize GLEW" << std::endl;
		Debug::FatalError("Failed to initialize GLEW! ", "Window.cpp ", __LINE__);
		return false;
	}

	
	//std::cout << "OpenGL version: " << glGetString(GL_VER ION) << std::endl;
	Debug::Info("OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)), "Window.cpp ", __LINE__);
	
	glViewport(0, 0, width, height);

	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth() const
{
	return width;
}

int Window::GetHeight() const
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//get rid of any deprecated functions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	//Using version 4.5, If GPU is very old, try 4.1, 3.3
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// set the swap interval to be equal and synchronized with the vertical retrace of the screen.
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;

}	

void Window::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);// 32bit
}
