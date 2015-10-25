#include "stdafx.h"
#include "Universe.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

namespace
{
	const float UNIVERSE_WIDTH = 800;
	const float UNIVERSE_HEIGHT = 600;
}

void Universe::update(float dt)
{

	// On the ground.
	if (playerY < 0.001f) {
		playerVelocityX += (rightPressed - leftPressed) * walkAcceleration * dt;
		playerVelocityX = copysign(max(0.0f, fabs(playerVelocityX) - frictionAcceleration * dt), playerVelocityX);
		playerVelocityX = max(-maxWalkVelocity, std::min(maxWalkVelocity, playerVelocityX));

		if (upPressed) {
			playerVelocityY = jumpVelocity;
		}
	}

	playerVelocityY -= gravityAcceleration * dt;

	playerX += playerVelocityX * dt;
	playerY += playerVelocityY * dt;

	// Clamp position.
	if (playerX < 0)
	{
		playerX = 0.0f;
		playerVelocityX = 0.0f;
	}
	else if (playerX > UNIVERSE_WIDTH - playerWidth)
	{
		playerX = UNIVERSE_WIDTH - playerWidth;
		playerVelocityX = 0.0f;
	}

	if (playerY < 0)
	{
		playerY = 0.0f;
		playerVelocityY = 0.0f;
	}
	else if (playerY > UNIVERSE_HEIGHT - playerHeight)
	{
		playerY = UNIVERSE_HEIGHT - playerHeight;
		playerVelocityY = 0.0f;
	}
}
