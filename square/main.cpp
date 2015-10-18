#include "stdafx.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct SDL {
public:
	~SDL() {
		SDL_Quit();
	}
};

struct SDL_WindowDeleter
{
	void operator()(SDL_Window *window) const
	{
		SDL_DestroyWindow(window);
	}
};

struct SDL_GLContextDeleter {
	void operator()(SDL_GLContext glContext) const
	{
		SDL_GL_DeleteContext(glContext);
	}
};

int main( int argc, char* args[] )
{
		SDL sdl;
    if(SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
				return 1;
    }

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		std::unique_ptr<SDL_Window, SDL_WindowDeleter> window(SDL_CreateWindow(
				"SDL Tutorial",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN));

    if(!window)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
				return 1;
    }

		std::unique_ptr<void, SDL_GLContextDeleter> glContext(SDL_GL_CreateContext(window.get()));

		glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 1.0f, 1.0f);
		glRectf(0.0, 0.0, 100.0, 100.0);
		SDL_GL_SwapWindow(window.get());

		SDL_Delay(2000);
    return 0;
}
