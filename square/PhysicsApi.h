#pragma once
#ifndef SQUARE_PHYSICS_API_H
#define SQUARE_PHYSICS_API_H

#include <memory>
#include <glm/glm.hpp>

class AABBCollider {
public:
	glm::vec2 min;
	glm::vec2 max;
	glm::vec2 velocity = glm::vec2(0, 0);
	glm::vec2 normal = glm::vec2(0, 0);
	bool fixed;
};

class PhysicsFactory {
public:
	virtual std::shared_ptr<AABBCollider> newAABBCollider() = 0;
};

#endif // SQUARE_PHYSICS_API_H