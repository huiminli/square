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
  for (auto sprite : mPlayer.getSprites())
  {
    sprites.push_back(RenderableSprite{ sprite.x, sprite.y, sprite.spriteIndex });
  }
  return sprites;
}

void Universe::update(float dt)
{
  mPlayer.update(leftPressed, rightPressed, upPressed, rightPressed, dt);
}
