#include "stdafx.h"
#include "Player.h"
#include "Universe.h"

using std::copysign;
using std::fabs;
using std::max;
using std::min;

using namespace UNIVERSE;

Player::Player()
{
  sprites.push_back(RenderableSprite{ 0.0f, 0.0f, 6 });
  sprites.push_back(RenderableSprite{ 0.0f, 32.0f, 5 });
}

std::vector<RenderableSprite> Player::getSprites() const
{
  return sprites;
}

// TODO: put the pressed control into a struct
void Player::update(bool leftPressed, bool rightPressed, bool upPressed, bool downPressed, float dt)
{
  bool onGround = playerY < 0.001f;
  
  playerVelocityX += (rightPressed - leftPressed) * walkAcceleration * dt * (onGround ? 1.0f : 0.15f) ;
  playerVelocityX = max(-maxWalkVelocity, std::min(maxWalkVelocity, playerVelocityX));
  
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
  else if (playerX > UNIVERSE::UNIVERSE_WIDTH - playerWidth)
  {
    playerX = UNIVERSE::UNIVERSE_WIDTH - playerWidth;
    playerVelocityX = 0.0f;
  }
  
  if (playerY < 0)
  {
    playerY = 0.0f;
    playerVelocityY = 0.0f;
  }
  else if (playerY > UNIVERSE::UNIVERSE_HEIGHT - playerHeight)
  {
    playerY = UNIVERSE::UNIVERSE_HEIGHT - playerHeight;
    playerVelocityY = 0.0f;
  }
  
  for (int i = 0; i < sprites.size(); ++i)
  {
    RenderableSprite &sprite = sprites[i];
    sprite.x = playerX;
    // TODO: currently naively just assume y coord is based on the order in sprites,
    // but really this should be stored in the fields in Sprites.
    sprite.y = playerY + i * 32;
  }
}
