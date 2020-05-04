#include "common/SDL_Util.h"
#include "core/Scene.h"
#include "game/Block.h"
#include "game/Player.h"

using game::BlockType;
using game::Player;

namespace {

  const unsigned UNIVERSE_TICK_MS = 10;

	const unsigned BACKGROUND_SIZE_X = 16;
	const unsigned BACKGROUND_SIZE_Y = 16;

	const BlockType BLOCK_TYPES[] = { 
		BlockType(0,   true),  //  0 - Rock. 
		BlockType(108, false), //  1 - Sky.

		BlockType(1,   false), //  2 - Hill (tip).
		BlockType(16,  false), //  3 - Hill (left edge).
		BlockType(17,  false), //  4 - Hill (interior dots).
		BlockType(18,  false), //  5 - Hill (right edge).
		BlockType(19,  false), //  6 - Hill (interior green).

		BlockType(112, false), //  7 - Cloud.
		BlockType(113, false), //  8 - Cloud.
		BlockType(114, false), //  9 - Cloud.
		BlockType(128, false), // 10 - Cloud.
		BlockType(129, false), // 11 - Cloud.
		BlockType(130, false), // 12 - Cloud.
	};

	const unsigned char BACKGROUND_BLOCKS[BACKGROUND_SIZE_X * BACKGROUND_SIZE_Y] = {
		1,  1,  0,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  0,
		1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		1,  1,  0,  1,  0,  1,  1,  1,  1,  7,  8,  9,  1,  1,  1,  0,
		1,  1,  1,  1,  1,  1,  1,  1,  1,  10, 11, 12, 1,  1,  1,  0,
		1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1,  0,
		1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		1,  1,  2,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		1,  3,  4,  5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		3,  4,  6,  4,  5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	};

	//const unsigned char BACKGROUND_BLOCKS[BACKGROUND_SIZE_X * BACKGROUND_SIZE_Y] = {
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  7,  8,  9,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  11, 11, 12, 1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  3,  4,  5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	3,  4,  6,  4,  5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//	1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	//};

}  // namespace

void mainLoop();

int main( int argc, char* args[] )
{
	mainLoop();
	return 0;
}

void mainLoop() {
	SDL sdl;
	sdl.initialize();

	core::Scene scene;
	scene.initialize();

	for (unsigned char x = 0; x < BACKGROUND_SIZE_X; ++x) {
		for (unsigned char y = 0; y < BACKGROUND_SIZE_Y; ++y) {
			const BlockType *blockType = &BLOCK_TYPES[BACKGROUND_BLOCKS[y * BACKGROUND_SIZE_X + x]];
			scene.addEntity(std::make_unique<game::Block>(scene, glm::vec2(x, BACKGROUND_SIZE_Y - 1 - y), blockType));
		}
	}

	scene.addEntity(std::make_unique<Player>(scene, glm::vec2(0, 10)));

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
			scene.update(UNIVERSE_TICK_MS / 1000.0f);
		}

		scene.render();
	}
}
