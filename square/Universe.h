#pragma once
#ifndef SQUARE_UNIVERSE_H
#define SQUARE_UNIVERSE_H

#include <list>
#include "Entity.h"
#include "EntityFactory.h"
#include "RenderableSprite.h"
#include "Player.h"

class Universe : public EntityFactory {
public:
	void update(float dt);
	void addEntity(std::unique_ptr<Entity> entity);

  std::list<std::weak_ptr<RenderableSprite>> getSprites() const;
	std::shared_ptr<RenderableSprite> newRenderableSprite() override;

private:
	std::list<std::unique_ptr<Entity>> entities;
	std::list<std::weak_ptr<RenderableSprite>> sprites;
};

#endif // SQUARE_UNIVERSE_H