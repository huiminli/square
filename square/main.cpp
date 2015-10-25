#include "stdafx.h"
#include "Renderer.h"
#include "SDL_Util.h"
#include "Universe.h"

namespace {
  const unsigned UNIVERSE_TICK_MS = 10;
}

void mainLoop();

int main( int argc, char* args[] )
{
	try
	{
		mainLoop();
		return 0;
	}
	catch (std::exception &e)
	{
		SDL_Log("Top level exception: %s", e.what());
		throw e;
	}
}

void mainLoop() {
	SDL sdl;
	sdl.initialize();

	Renderer renderer;
	renderer.initialize();

	Universe universe;
	unsigned lastSimulationTimeMs = SDL_GetTicks();
	while (true) {
		unsigned now = SDL_GetTicks();

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				return;
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

		renderer.render(universe);
	}
}
