#pragma once
#ifndef SQUARE_PLAYER_H
#define SQUARE_PLAYER_H

#include "Entity.h"

class Camera;
class Collider;
class EntityFactory;
class RenderableSprite;

class Block : public Entity {
public:
	Block(EntityFactory &ef, float x, float y, unsigned tile);

private:
	std::shared_ptr<RenderableSprite> sprite;
};

class Player : public Entity {
public:
  Player(EntityFactory &ef);
  void update(float dt) override;

private:
  const float maxWalkVelocity = 7.0f;
	const float airAcceleration = 20.0f;
  const float walkAcceleration = 300.0f;
  const float jumpVelocity = 20.0f;
	const float cameraVelocity = 3.0f;
  
	Camera *camera;
  std::shared_ptr<RenderableSprite> sprite;
	std::shared_ptr<Collider> collider;
};

#endif // SQUARE_PLAYER_H