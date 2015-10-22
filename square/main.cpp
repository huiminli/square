#include "stdafx.h"

namespace {
  const int SCREEN_WIDTH = 800;
  const int SCREEN_HEIGHT = 600;
  const int UNIVERSE_TICK_MS = 10;
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
		
		// On the ground.
		if (playerY < 0.001f) {
			playerVelocityX += (rightPressed - leftPressed) / 90.0f;
			playerVelocityY += (upPressed - downPressed) / 2.0f;
			playerVelocityX = std::max(-playerMaxVelocity, std::min(playerMaxVelocity, playerVelocityX));

			if (playerVelocityX >= 0.0f) {
				playerVelocityX = std::max(0.0f, playerVelocityX - friction * dt);
			}
			else {
				playerVelocityX = std::min(0.0f, playerVelocityX + friction * dt);
			}
		}

		playerVelocityY -= gravity * dt;

		playerX += playerVelocityX * dt;
		playerY += playerVelocityY * dt;

		// Clamp position.
		if (playerX < 0) 
		{
			playerX = 0.0f;
			playerVelocityX = 0.0f;
		}
		else if (playerX > SCREEN_WIDTH - playerWidth)
		{
			playerX = SCREEN_WIDTH - playerWidth;
			playerVelocityX = 0.0f;
		}

		if (playerY < 0)
		{
			playerY = 0.0f;
			playerVelocityY = 0.0f;
		}
		else if (playerY > SCREEN_HEIGHT - playerHeight)
		{
			playerY = SCREEN_HEIGHT - playerHeight;
			playerVelocityY = 0.0f;
		}
	}

	bool upPressed = false;
	bool downPressed = false;
	bool leftPressed = false;
	bool rightPressed = false;
	float playerX = 0.0f;
	float playerY = 0.0f;
	float playerVelocityX = 0.0f;
	float playerVelocityY = 0.0f;
	float playerMaxVelocity = 0.2f;
	float playerWidth = 32.0f;
	float playerHeight = 32.0f;
	float friction = 1 / 3000.0f;
	float gravity = 1 / 1000.0f;
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

    if (now - lastSimulationTimeMs < UNIVERSE_TICK_MS) {
      SDL_WaitEventTimeout(NULL, now - lastSimulationTimeMs);
      continue;
    }

    while (now - lastSimulationTimeMs >= UNIVERSE_TICK_MS) {
      lastSimulationTimeMs += UNIVERSE_TICK_MS;
			universe.update(UNIVERSE_TICK_MS);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRectf(
			universe.playerX,
			universe.playerY,
			universe.playerX + universe.playerWidth,
			universe.playerY + universe.playerHeight);

    SDL_GL_SwapWindow(window.get());
  }
}
