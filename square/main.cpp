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

int main( int argc, char* args[] )
{
		SDL sdl;
    if(SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
				return 1;
    }

		std::unique_ptr<SDL_Window, SDL_WindowDeleter> window(SDL_CreateWindow(
				"SDL Tutorial",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN));

    if(!window)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
				return 1;
    }

		SDL_Surface* screenSurface = SDL_GetWindowSurface(window.get());
    SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
		SDL_UpdateWindowSurface(window.get());
		SDL_Delay(2000);
    
    return 0;
}
