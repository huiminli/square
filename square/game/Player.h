#pragma once
#include "../core/Entity.h"
#include "../core/EntityFactory.h"
#include "../graphics/api/Camera.h"
#include "../graphics/api/Sprite.h"
#include "../physics/api/AABBCollider.h"

namespace game {

  class Player : public core::Entity {
  public:
    Player(core::EntityFactory& ef, const glm::vec2& position);
    void update(float dt) override;

  private:
    glm::vec2 starting_position_;
    graphics::api::Camera* camera;
    std::shared_ptr<graphics::api::Sprite> sprite;
    std::shared_ptr<physics::api::AABBCollider> collider;
  };

} // namespace game