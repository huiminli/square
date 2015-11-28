#pragma once
#ifndef SQUARE_COLLIDER_H
#define SQUARE_COLLIDER_H

#include <glm/glm.hpp>

class Collider {
public:
	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 velocity;
	glm::vec2 acceleration;
	bool fixed;
};

#endif // SQUARE_COLLIDER_H