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
	sprite = ef.newRenderableSprite();
	sprite->tileIndex = 6;


}

// TODO: put the pressed control into a struct
void Player::update(float dt)
{
	bool rightPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_RIGHT] != 0;
	bool leftPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_LEFT] != 0;
	bool upPressed = SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_UP] != 0;

  bool onGround = y < 0.001f;
  
  velocityX += (rightPressed - leftPressed) * walkAcceleration * dt * (onGround ? 1.0f : 0.15f) ;
  velocityX = max(-maxWalkVelocity, std::min(maxWalkVelocity, velocityX));
  
  if (onGround) {
		velocityX = copysign(max(0.0f, fabs(velocityX) - frictionAcceleration * dt), velocityX);
    
    if (upPressed) {
      velocityY = jumpVelocity;
    }
  }
  
	velocityY -= gravityAcceleration * dt;
  
  x += velocityX * dt;
  y += velocityY * dt;
  
  if (y < 0)
  {
    y = 0.0f;
		velocityY = 0.0f;
  }

	sprite->x = x;
	sprite->y = y;
}
