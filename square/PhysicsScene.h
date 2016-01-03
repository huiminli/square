#pragma once
#ifndef SQUARE_PHYSICS_SYSTEM_H
#define SQUARE_PHYSICS_SYSTEM_H

#include <list>
#include <memory>
#include "PhysicsApi.h"

class PhysicsScene : public PhysicsFactory {
public:
	void processCollision(float dt);
	std::shared_ptr<AABBCollider> newAABBCollider();

private:
	std::list<std::shared_ptr<AABBCollider>> colliders;
};

#endif // SQUARE_PHYSICS_SYSTEM_H