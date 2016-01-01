#pragma once
#ifndef SQUARE_PHYSICS_API_H
#define SQUARE_PHYSICS_API_H

#include <memory>
#include <glm/glm.hpp>

class Collider {
public:
	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	bool fixed;
};

class PhysicsFactory {
public:
	virtual std::shared_ptr<Collider> newCollider() = 0;
};

#endif // SQUARE_PHYSICS_API_H