#pragma once
#include <list>
#include <memory>
#include "api/System.h"
#include "api/AABBCollider.h"

namespace physics {

class PhysicsScene : public api::System {
public:
	void processCollision(float dt);
	std::shared_ptr<api::AABBCollider> newAABBCollider();

private:
	std::list<std::shared_ptr<api::AABBCollider>> colliders;
};

}  // namespace physics
