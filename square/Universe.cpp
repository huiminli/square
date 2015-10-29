#include "stdafx.h"
#include "Universe.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

std::list<std::weak_ptr<RenderableSprite>> Universe::getSprites() const
{
  return sprites;
}

void Universe::update(float dt)
{
  mPlayer->update(leftPressed, rightPressed, upPressed, rightPressed, dt);
}

std::shared_ptr<RenderableSprite> Universe::newRenderableSprite() {
	auto result = std::make_shared<RenderableSprite>();
	sprites.push_back(result);
	return result;
}
