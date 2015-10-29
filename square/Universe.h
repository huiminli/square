#pragma once
#ifndef SQUARE_UNIVERSE_H
#define SQUARE_UNIVERSE_H

#include <list>
#include "RenderableSprite.h"
#include "Player.h"

class Player;

namespace UNIVERSE
{
  const float UNIVERSE_WIDTH = 800;
  const float UNIVERSE_HEIGHT = 600;
}

class Universe {
public:
	Universe();
	void update(float dt);
  std::list<RenderableSprite> getSprites() const;

	bool upPressed = false;
	bool downPressed = false;
	bool leftPressed = false;
	bool rightPressed = false;

public:
  Player mPlayer;
};

#endif // SQUARE_UNIVERSE_H