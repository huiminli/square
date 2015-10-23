#include "stdafx.h"

namespace {
  const unsigned SCREEN_WIDTH = 800;
  const unsigned SCREEN_HEIGHT = 600;
  const unsigned UNIVERSE_TICK_MS = 10;
}

using std::copysign;
using std::fabs;
using std::max;
using std::min;

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

struct SDL_SurfaceDeleter {
	void operator()(SDL_Surface *surface) const
	{
		SDL_FreeSurface(surface);
	}
};

struct Universe {
public:
	void update(float dt) {
		
		// On the ground.
		if (playerY < 0.001f) {
			playerVelocityX += (rightPressed - leftPressed) * walkAcceleration * dt;
			playerVelocityX = copysign(max(0.0f, fabs(playerVelocityX) - frictionAcceleration * dt), playerVelocityX);
			playerVelocityX = max(-maxWalkVelocity, std::min(maxWalkVelocity, playerVelocityX));

			if (upPressed) {
				playerVelocityY = jumpVelocity;
			}
		}

		playerVelocityY -= gravityAcceleration * dt;

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

	const float playerWidth = 32.0f;
	const float playerHeight = 32.0f;
	const float maxWalkVelocity = 200.0f;
	const float frictionAcceleration = 1000.0f;
	const float gravityAcceleration = 1000.0f;
	const float walkAcceleration = 10000.0f;
	const float jumpVelocity = 500.0f;
};


int main( int argc, char* args[] )
{
  SDL sdl;
  if(SDL_Init( SDL_INIT_VIDEO ) < 0)
  {
      printf("SDL_Init: %s\n", SDL_GetError());
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
      printf("SDL_CreateWindow: %s\n", SDL_GetError());
      return 1;
  }


	std::unique_ptr<void, SDL_GLContextDeleter> glContext(SDL_GL_CreateContext(window.get()));
	glEnable(GL_TEXTURE_2D);
	glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, -1.0, 1.0);

	std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter> tiles(SDL_LoadBMP("mario.bmp"));
	if (!tiles) {
		printf("SDL_LoadBMP: %s\n", SDL_GetError());
		return 1;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		tiles->format->BytesPerPixel,
		tiles->w,
		tiles->h,
		0,
		GL_BGR,
		GL_UNSIGNED_BYTE,
		tiles->pixels);

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
			universe.update(UNIVERSE_TICK_MS / 1000.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
				glTexCoord2f(.0625f * 12, .0625f * 4);
				glVertex2f(universe.playerX, universe.playerY);

				glTexCoord2f(.0625f * 13, .0625f * 4);
				glVertex2f(universe.playerX + universe.playerWidth, universe.playerY);

				glTexCoord2f(.0625f * 13, .0625f * 3);
				glVertex2f(universe.playerX + universe.playerWidth, universe.playerY + universe.playerHeight);

				glTexCoord2f(.0625f * 12, .0625f * 3);
				glVertex2f(universe.playerX, universe.playerY + universe.playerHeight);
		glEnd();

    SDL_GL_SwapWindow(window.get());
  }

	glDeleteTextures(1, &texture);
}
