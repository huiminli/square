#include "stdafx.h"
#include "PhysicsScene.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

void PhysicsScene::processCollision(float dt) {
	for (auto &collider_weak : colliders) {
		if (auto collider = collider_weak.lock()) {
			if (collider->fixed) {
				continue;
			}

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

std::shared_ptr<Collider> PhysicsScene::newCollider() {
	auto result = std::make_shared<Collider>();
	colliders.push_back(result);
	return result;
}
