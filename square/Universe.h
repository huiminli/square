#pragma once
#ifndef SQUARE_UNIVERSE_H
#define SQUARE_UNIVERSE_H

#include <list>
#include "RenderableSprite.h"

class Universe {
public:
	Universe();
	void update(float dt);

	bool upPressed = false;
	bool downPressed = false;
	bool leftPressed = false;
	bool rightPressed = false;

	float playerX = 0.0f;
	float playerY = 0.0f;
	float playerVelocityX = 0.0f;
	float playerVelocityY = 0.0f;

	const float playerWidth = 32.0f;
	const float playerHeight = 32.0f;
	const float maxWalkVelocity = 200.0f;
	const float frictionAcceleration = 1000.0f;
	const float gravityAcceleration = 1000.0f;
	const float walkAcceleration = 10000.0f;
	const float jumpVelocity = 500.0f;

	std::list<RenderableSprite> sprites;
};

#endif // SQUARE_UNIVERSE_H