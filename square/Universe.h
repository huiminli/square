#pragma once
#ifndef SQUARE_UNIVERSE_H
#define SQUARE_UNIVERSE_H

#include <list>
#include "Collider.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "RenderableSprite.h"

class Universe : public EntityFactory {
public:
	void update(float dt);
	void addEntity(std::unique_ptr<Entity> entity);

	Camera* getCamera() override { return &camera; }
	const Camera* getCamera() const { return &camera; }
	std::shared_ptr<Collider> newCollider() override;
  std::list<std::weak_ptr<RenderableSprite>> getRenderableSprites() const;
	std::shared_ptr<RenderableSprite> newRenderableSprite() override;

private:
	// Gameplay.
	std::list<std::unique_ptr<Entity>> entities;

	// Rendering.
	Camera camera;
	std::list<std::weak_ptr<RenderableSprite>> sprites;

	// Collision.
	std::list<std::weak_ptr<Collider>> colliders;
};

#endif // SQUARE_UNIVERSE_H