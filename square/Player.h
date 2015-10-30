#pragma once
#ifndef SQUARE_PLAYER_H
#define SQUARE_PLAYER_H

#include "Entity.h"

class Camera;
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

private:
  float x = 0.0f;
  float y = 0.0f;
  float velocityX = 0.0f;
  float velocityY = 0.0f;
  
  const float maxWalkVelocity = 7.0f;
  const float frictionAcceleration = 30.0f;
  const float gravityAcceleration = 30.0f;
  const float walkAcceleration = 300.0f;
  const float jumpVelocity = 20.0f;
	const float cameraVelocity = 3.0f;
  
	Camera *camera;
  std::shared_ptr<RenderableSprite> sprite;
};

#endif // SQUARE_PLAYER_H