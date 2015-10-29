#include "stdafx.h"
#include "Universe.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

Universe::Universe() {}

std::list<RenderableSprite> Universe::getSprites() const
{
  std::list<RenderableSprite> sprites;

	for (unsigned char i = 0; i < 128; ++i) {
		sprites.push_back(RenderableSprite{ 32.0f * (i % 16), 32.0f * (10 - i / 16) , i / 16 });
	}

  for (auto sprite : mPlayer.getSprites())
  {
    sprites.push_back(sprite);
  }

  return sprites;
}

void Universe::update(float dt)
{
  mPlayer.update(leftPressed, rightPressed, upPressed, rightPressed, dt);
}
