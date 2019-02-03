#pragma once
#ifndef SQUARE_PLAYER_H
#define SQUARE_PLAYER_H

#include "Entity.h"

class AABBCollider;
class Camera;
class EntityFactory;
class RenderableSprite;

class Player : public Entity {
public:
  Player(EntityFactory &ef, const glm::vec2 &position);
  void update(float dt) override;

private:
  glm::vec2 starting_position_;
	Camera *camera;
  std::shared_ptr<RenderableSprite> sprite;
	std::shared_ptr<AABBCollider> collider;
};

#endif // SQUARE_PLAYER_H