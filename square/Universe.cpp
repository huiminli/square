#include "stdafx.h"
#include "Universe.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

Universe::Universe()
{
//	for (unsigned char i = 0; i < 128; ++i) {
//		sprites.push_back(RenderableSprite{32.0f * (i % 16), 32.0f * (10 - i/16) , i});
//	}
//
//	sprites.push_back(RenderableSprite{ 0.0f, 0.0f, 0 });
}

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
