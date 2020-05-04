#pragma once
#include <memory>
#include "../core/Entity.h"
#include "../core/EntityFactory.h"
#include "../graphics/api/Sprite.h"
#include "../physics/api/AABBCollider.h"

namespace game {

	class BlockType {
	public:
		BlockType(unsigned tileIndex, bool collision) : tileIndex(tileIndex), collision(collision) {}

		unsigned getTileIndex() const { return tileIndex; }
		bool getCollision() const { return collision; }

	private:
		const unsigned tileIndex;
		const bool collision;
	};

	class Block : public core::Entity {
	public:
		Block(core::EntityFactory& ef, const glm::vec2& position, const BlockType* blockTemplate);
		void update(float dt) override;

	private:
		const BlockType* blockTemplate;
		std::shared_ptr<graphics::api::Sprite> sprite;
		std::shared_ptr<physics::api::AABBCollider> collider;
	};

} // game
