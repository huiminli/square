#pragma once
#ifndef SQUARE_PLAYER_H
#define SQUARE_PLAYER_H

#include "Entity.h"

class EntityFactory;
class RenderableSprite;

class Block : public Entity {
public:
	Block(EntityFactory &ef, float x, float y, unsigned tile);
	void update(float dt) override {}

private:
	std::shared_ptr<RenderableSprite> sprite;
};

class Player : public Entity {
public:
  Player(EntityFactory &ef);
  void update(float dt) override;

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