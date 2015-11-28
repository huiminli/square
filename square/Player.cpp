#include "stdafx.h"
#include "Player.h"
#include "Universe.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

Block::Block(EntityFactory & ef, float x, float y, unsigned tile)
{
	sprite = ef.newRenderableSprite();
	sprite->x = x;
	sprite->y = y;
	sprite->tileIndex = tile;
}

Player::Player(EntityFactory &ef)
{
	camera = ef.getCamera();

	sprite = ef.newRenderableSprite();
	sprite->tileIndex = 60;

	collider = ef.newCollider();
	collider->position = glm::vec4(0.0f, 0.0f, 32.0f, 32.0f);
	collider->velocity = glm::vec2(0.0f);
	collider->acceleration = glm::vec2(0.0f);
	collider->fixed = false;
}

// TODO: put the pressed control into a struct
void Player::update(float dt)
{
	bool rightPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT] != 0;
	bool leftPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT] != 0;
	bool upPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP] != 0;

  bool onGround = collider->position.y < 0.001f;
  
	collider->velocity.x += (rightPressed - leftPressed) * walkAcceleration * dt * (onGround ? 1.0f : 0.15f) ;
	collider->velocity.x = max(-maxWalkVelocity, min(maxWalkVelocity, collider->velocity.x));
  
  if (onGround) {
		collider->velocity.x = copysign(max(0.0f, fabs(collider->velocity.x) - frictionAcceleration * dt), collider->velocity.x);
    
    if (upPressed) {
			collider->velocity.y = jumpVelocity;
    }
  }
  
	collider->velocity.y -= gravityAcceleration * dt;
  
	collider->position.x += collider->velocity.x * dt;
	collider->position.y += collider->velocity.y * dt;
  
  if (collider->position.y < 0)
  {
		collider->position.y = 0.0f;
		collider->velocity.y = 0.0f;
  }

	sprite->x = collider->position.x;
	sprite->y = collider->position.y;

	bool wPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_W] != 0;
	bool sPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_S] != 0;
	bool aPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_A] != 0;
	bool dPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_D] != 0;
	camera->x += (dPressed - aPressed) * cameraVelocity * dt;
	camera->y += (wPressed - sPressed) * cameraVelocity * dt;
}
