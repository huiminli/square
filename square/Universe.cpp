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

Universe::Universe() {
	sprites.push_back(RenderableSprite{0.0f, 0.0f, 32.0f, 32.0f, SpriteType::A});
	sprites.push_back(RenderableSprite{32.0f, 32.0f, 64.0f, 64.0f, SpriteType::B });
	sprites.push_back(RenderableSprite{96.0f, 96.0f, 128.0f, 128.0f, SpriteType::C });
}

void Universe::update(float dt)
{
	bool onGround = playerY < 0.001f;

	playerVelocityX += (rightPressed - leftPressed) * walkAcceleration * dt * (onGround ? 1.0f : 0.15f) ;
	playerVelocityX = max(-maxWalkVelocity, std::min(maxWalkVelocity, playerVelocityX));

	// On the ground.
	if (onGround) {
		playerVelocityX = copysign(max(0.0f, fabs(playerVelocityX) - frictionAcceleration * dt), playerVelocityX);

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

	sprites.front().x = playerX;
	sprites.front().y = playerY;
}
