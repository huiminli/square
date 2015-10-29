#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "RenderableSprite.h"

class Player {
public:
  Player();
  void update(bool left, bool right, bool up, bool down, float dt);
  std::vector<RenderableSprite> getSprites() const;

public:
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
  
  std::vector<RenderableSprite> sprites;
};

#endif // PLAYER_H