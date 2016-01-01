#pragma once
#ifndef SQUARE_PHYSICS_SYSTEM_H
#define SQUARE_PHYSICS_SYSTEM_H

#include <list>
#include <memory>
#include "PhysicsApi.h"

class PhysicsScene : public PhysicsFactory {
public:
	void processCollision(float dt);
	std::shared_ptr<Collider> newCollider();

private:
	const float frictionAcceleration = 30.0f;
	const float gravityAcceleration = 30.0f;
	std::list<std::weak_ptr<Collider>> colliders;
};

#endif // SQUARE_PHYSICS_SYSTEM_H