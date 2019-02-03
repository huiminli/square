#pragma once
#ifndef SQUARE_PHYSICS_API_H
#define SQUARE_PHYSICS_API_H

#include <memory>
#include <glm/glm.hpp>

class AABBCollider {
public:
	glm::vec2 min;
  // Use size instead of max to prevent errors from accumulating.
  glm::vec2 size;
	glm::vec2 velocity = glm::vec2(0, 0);
  // Fixed means that this collider stays in place and doesn't move.
	bool fixed = false;

  // TODO(adrw): Use int ids instead of pointers.
  AABBCollider* top = nullptr;
  AABBCollider* bottom = nullptr;
  AABBCollider* left = nullptr;
  AABBCollider* right = nullptr;
  AABBCollider* inside = nullptr;

  glm::vec2 max() const {
    return min + size;
  }
};

class PhysicsFactory {
public:
	virtual std::shared_ptr<AABBCollider> newAABBCollider() = 0;
};

#endif // SQUARE_PHYSICS_API_H