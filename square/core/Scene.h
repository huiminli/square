#pragma once
#include <list>
#include "Entity.h"
#include "EntityFactory.h"
#include "../graphics/Renderer.h"
#include "../physics/PhysicsScene.h"

namespace core {

	class Scene : public EntityFactory {
	public:
		void initialize() { renderer.initialize(); }
		void update(float dt);
		void render() { renderer.render(); };
		void addEntity(std::unique_ptr<Entity> entity) { entities.push_back(std::move(entity)); }

		std::shared_ptr<physics::api::AABBCollider> newAABBCollider() override { return physics.newAABBCollider(); }
		graphics::api::Camera* getCamera() override { return renderer.getCamera(); }
		std::shared_ptr<graphics::api::Sprite> newSprite() override { return renderer.newSprite(); }
		graphics::api::SpriteGrid* newSpriteGrid() override { return renderer.newSpriteGrid(); }

	private:
		std::list<std::unique_ptr<Entity>> entities;
		graphics::Renderer renderer;
		physics::PhysicsScene physics;
	};

} // namespace core