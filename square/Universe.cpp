#include "stdafx.h"
#include "Universe.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

void Universe::update(float dt)
{
	// TODO(adrw): Maybe this should live outside of Universe?
	for (auto &entity : entities) {
		entity->update(dt);
	}
}

void Universe::addEntity(std::unique_ptr<Entity> entity) {
	entities.push_back(std::move(entity));
}

std::shared_ptr<RenderableSprite> Universe::newRenderableSprite() {
	auto result = std::make_shared<RenderableSprite>();
	sprites.push_back(result);
	return result;
}

std::list<std::weak_ptr<RenderableSprite>> Universe::getSprites() const
{
	return sprites;
}
