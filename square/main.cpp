#include "stdafx.h"

namespace {
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;
  const int GAME_FRAME_MS = 10;
}

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

struct Universe {
public:
	void update(long dt) {
		x += (rightPressed - leftPressed) * dt / 20.0f + dt / 1000.0f; 
		y += (upPressed - downPressed) * dt / 20.0f + dt / 1000.0f;
	}

	bool upPressed = false;
	bool downPressed = false;
	bool leftPressed = false;
	bool rightPressed = false;
	float x = 0.0f;
	float y = 0.0f;
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


	Universe universe;
  unsigned lastSimulationTimeMs = SDL_GetTicks();
  while (true) {
    unsigned now = SDL_GetTicks();

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
      {
        return 0;
      }
			else if (e.type == SDL_KEYDOWN)
      {
        switch (e.key.keysym.sym) {
          case SDLK_UP: universe.upPressed = true; break;
          case SDLK_DOWN: universe.downPressed = true; break;
          case SDLK_LEFT: universe.leftPressed = true; break;
          case SDLK_RIGHT: universe.rightPressed = true; break;
        }
      }
			else if (e.type == SDL_KEYUP)
			{
				switch (e.key.keysym.sym) {
				case SDLK_UP: universe.upPressed = false; break;
				case SDLK_DOWN: universe.downPressed = false; break;
				case SDLK_LEFT: universe.leftPressed = false; break;
				case SDLK_RIGHT: universe.rightPressed = false; break;
				}
			}
    }

    if (now - lastSimulationTimeMs < GAME_FRAME_MS) {
      SDL_WaitEventTimeout(NULL, now - lastSimulationTimeMs);
      continue;
    }

    while (now - lastSimulationTimeMs >= GAME_FRAME_MS) {
      lastSimulationTimeMs += GAME_FRAME_MS;
			universe.update(GAME_FRAME_MS);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(universe.x, universe.y, universe.x + 100.0f, universe.y + 100.0f);

    SDL_GL_SwapWindow(window.get());
  }
}
