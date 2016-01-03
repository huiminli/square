#include "stdafx.h"
#include "PhysicsScene.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

namespace {
	const float frictionAcceleration = 100.0f;
	const float gravityAcceleration = 30.0f;
	const float INF = std::numeric_limits<float>::infinity();
}

void PhysicsScene::processCollision(float dt) {
	for (auto &collider : colliders) {
		if (collider.use_count() == 1) {
			// TODO(adrw): garbage collect.
			continue;
		}

		if (collider->fixed) {
			continue;
		}


		float firstCollisionTime = dt;
		glm::vec2 firstCollisionNormal = glm::vec2(0, 0);

		// Check collision.
		for (auto &other : colliders) {
			if (collider.get() != other.get()) {
				glm::vec2 xPenetration = glm::vec2(other->min.x - collider->max.x, other->max.x - collider->min.x);
				if (collider->velocity.x < 0.0f) {
					xPenetration = glm::vec2(xPenetration.t, xPenetration.s);
				}
				glm::vec2 xPenetrationTime = glm::vec2(INF, INF);
				if (collider->velocity.x != 0.0) {
					xPenetrationTime = xPenetration / collider->velocity.x;
				}
				else if (xPenetration.s < 0.0f && xPenetration.t > 0.0f) {
					xPenetrationTime = glm::vec2(-INF, INF);
				}

				glm::vec2 yPenetration = glm::vec2(other->min.y - collider->max.y, other->max.y - collider->min.y);
				if (collider->velocity.y < 0.0f) {
					yPenetration = glm::vec2(yPenetration.t, yPenetration.s);
				}
				glm::vec2 yPenetrationTime = glm::vec2(INF, INF);
				if (collider->velocity.y != 0.0f) {
					yPenetrationTime = yPenetration / collider->velocity.y;
				}
				else if (yPenetration.s < 0.0f && yPenetration.t > 0.0f) {
					yPenetrationTime = glm::vec2(-INF, INF);
				}

				glm::vec2 penetrationTime = glm::vec2(
					max(xPenetrationTime.s, yPenetrationTime.s),
					min(xPenetrationTime.t, yPenetrationTime.t));

				if (penetrationTime.t > penetrationTime.s
					&& penetrationTime.s >= 0.0f
					&& penetrationTime.s < firstCollisionTime) {
					firstCollisionTime = penetrationTime.s;
					firstCollisionNormal = (xPenetrationTime.s > yPenetrationTime.s)
						? glm::vec2(-copysign(1.0f, collider->velocity.x), 0.0f)
						: glm::vec2(0.0f, -copysign(1.0f, collider->velocity.y));
				}
			}
		}

		// Euler integration.
		collider->min += collider->velocity * firstCollisionTime;
		collider->max += collider->velocity * firstCollisionTime;
		collider->normal = firstCollisionNormal;

		if (glm::length2(collider->normal) > 0.0f) {
			glm::vec2 swappedNormal = glm::vec2(collider->normal.y, collider->normal.x);
			collider->velocity = glm::dot(collider->velocity, swappedNormal) * swappedNormal;
		}

		// TODO(adrw): Sliding without checking for collision.
		collider->min += collider->velocity * (dt - firstCollisionTime);
		collider->max += collider->velocity * (dt - firstCollisionTime);

		// TODO(adrw): Applying gravity and friction for the whole frame is a simplification.
		// Gravity & friction.
		if (collider->normal.y > 0.999f) {
			collider->velocity.x = copysign(max(0.0f, fabs(collider->velocity.x) - frictionAcceleration * dt), collider->velocity.x);
		} else {
			collider->velocity.y -= gravityAcceleration * dt;
		}
	}
}

std::shared_ptr<AABBCollider> PhysicsScene::newAABBCollider() {
	auto result = std::make_shared<AABBCollider>();
	colliders.push_back(result);
	return result;
}
