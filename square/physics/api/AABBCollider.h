#pragma once
#include <glm/glm.hpp>

namespace physics {
namespace api {

class AABBCollider {
public:
  glm::vec2 position_min;
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

  glm::vec2 position_max() const {
    return position_min + size;
  }
};

} // namespace api
} // namespace physics