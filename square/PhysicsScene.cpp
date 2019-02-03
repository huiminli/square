#include "stdafx.h"
#include "PhysicsScene.h"
#include "glm_ext.h"

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
  std::cout << "PhysicsScene::processCollision" << std::endl;

  for (auto &collider : colliders) {
    if (collider.use_count() == 1) {
      // TODO(adrw): garbage collect.
      continue;
    }

    if (collider->fixed) {
      continue;
    }

    // TODO(adrw): Applying gravity and friction for the whole frame is a simplification.
    // TODO(adrw): Possibly move it to a more central place.
    // Gravity & friction. 
    if (collider->bottom) {
      collider->velocity.x = copysign(max(0.0f, fabs(collider->velocity.x) - frictionAcceleration * dt), collider->velocity.x);
    }
    else {
      collider->velocity.y -= gravityAcceleration * dt;
    }

    collider->top = nullptr;
    collider->bottom = nullptr;
    collider->right = nullptr;
    collider->left = nullptr;

    // Find first collision. Process response. Repeat until time is left.
    float timeLeft = dt;
    while (timeLeft > 0.0f) {

      std::cout << "PhysicsScene::processCollision timeLeft=" << timeLeft << std::endl;

      float collisionTime = timeLeft;
      glm::vec2 collisionNormal = glm::vec2(0, 0);

      // Find first collision.
      for (auto &other : colliders) {
        if (collider.get() == other.get()) {
          continue;
        }

        glm::vec2 xPenetration = glm::vec2(other->min.x - collider->max().x, other->max().x - collider->min.x);
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

        glm::vec2 yPenetration = glm::vec2(other->min.y - collider->max().y, other->max().y - collider->min.y);
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
          && penetrationTime.s < collisionTime) {
          collisionTime = penetrationTime.s;

          if (xPenetrationTime.s > yPenetrationTime.s) {
            if (collider->velocity.x > 0) {
              collider->right = other.get();
              collisionNormal = glm::vec2(-1.0f, 0.0f);
            }
            else if (collider->velocity.x < 0) {
              collider->left = other.get();
              collisionNormal = glm::vec2(1.0f, 0.0f);
            }
            else {
              collider->inside = other.get();
            }
          } else {
            if (collider->velocity.y > 0) {
              collider->top = other.get();
              collisionNormal = glm::vec2(0.0f, -1.0f);
            }
            else if (collider->velocity.y < 0) {
              collider->bottom = other.get();
              collisionNormal = glm::vec2(0.0f, 1.0f);
            }
            else {
              collider->inside = other.get();
            }
          }
        }
      }


      // Euler integration.
      timeLeft -= collisionTime;
      collider->min += collider->velocity * collisionTime;

      if (glm::length2(collisionNormal) > 0.0f) {
        glm::vec2 perpencicularNormal = glm::vec2(collisionNormal.y, collisionNormal.x);
        collider->velocity = glm::dot(collider->velocity, perpencicularNormal) * perpencicularNormal;
      }
    }
  }
}

std::shared_ptr<AABBCollider> PhysicsScene::newAABBCollider() {
  auto result = std::make_shared<AABBCollider>();
  colliders.push_back(result);
  return result;
}
