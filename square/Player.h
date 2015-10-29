#pragma once
#ifndef SQUARE_PLAYER_H
#define SQUARE_PLAYER_H

class EntityFactory;
class RenderableSprite;

class Player {
public:
  Player(EntityFactory &ef);
  void update(bool left, bool right, bool up, bool down, float dt);

public:
  float x = 0.0f;
  float y = 0.0f;
  float velocityX = 0.0f;
  float velocityY = 0.0f;
  
  const float maxWalkVelocity = 200.0f;
  const float frictionAcceleration = 1000.0f;
  const float gravityAcceleration = 1000.0f;
  const float walkAcceleration = 10000.0f;
  const float jumpVelocity = 500.0f;
  
  std::shared_ptr<RenderableSprite> sprite;
};

#endif // SQUARE_PLAYER_H