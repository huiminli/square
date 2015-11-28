#include "stdafx.h"
#include "Universe.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

void Universe::update(float dt)
{
	processCollision(dt);

	// TODO(adrw): Maybe this should live outside of Universe?
	for (auto &entity : entities) {
		entity->update(dt);
	}
}

void Universe::processCollision(float dt) {
	for (auto &collider_weak : colliders) {
		if (auto collider = collider_weak.lock()) {
			collider->velocity.y -= gravityAcceleration * dt;
			collider->position += collider->velocity * dt;

			// Ground.
			if (collider->position.y < 0)
			{
				collider->position.y = 0.0f;
				collider->velocity.y = 0.0f;
			}

			// Friction.
			if (collider->position.y < 0.001f) {
				collider->velocity.x = copysign(max(0.0f, fabs(collider->velocity.x) - frictionAcceleration * dt), collider->velocity.x);
			}
		}
		else
		{
			// TODO(adrw): Remove unused weak_ptrs from here.
		}
	}
}

void Universe::addEntity(std::unique_ptr<Entity> entity) {
	entities.push_back(std::move(entity));
}

std::shared_ptr<Collider> Universe::newCollider() {
	auto result = std::make_shared<Collider>();
	colliders.push_back(result);
	return result;
}

std::shared_ptr<RenderableSprite> Universe::newRenderableSprite() {
	auto result = std::make_shared<RenderableSprite>();
	// TODO(adrw): Remove unused weak_ptrs from here.
	sprites.push_back(result);
	return result;
}

std::list<std::weak_ptr<RenderableSprite>> Universe::getRenderableSprites() const
{
	return sprites;
}
