#include "stdafx.h"
#include "SDL_Util.h"
#include "Player.h"
#include "Renderer.h"
#include "Universe.h"

namespace {
  const unsigned UNIVERSE_TICK_MS = 10;
}

void mainLoop();

int main( int argc, char* args[] )
{
	mainLoop();
	return 0;
}

void mainLoop() {
	SDL sdl;
	sdl.initialize();

	Renderer renderer;
	renderer.initialize();

	Universe universe;

	/*for (unsigned char i = 0; i < 128; ++i) {
		universe.addEntity(std::make_unique<Block>(universe, float(i % 16), float(20 - i / 16), i / 16));
	}*/

	universe.addEntity(std::make_unique<Player>(universe));

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
