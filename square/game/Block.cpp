#include "stdafx.h"
#include "Block.h"

namespace game {

Block::Block(core::EntityFactory& ef, const glm::vec2 &position, const BlockType *blockTemplate)
	: blockTemplate(blockTemplate)
{
	this->sprite = ef.newSprite();
	this->sprite->position = position;
	this->sprite->tileIndex = blockTemplate->getTileIndex();

	if (blockTemplate->getCollision()) {
		this->collider = ef.newAABBCollider();
		this->collider->position_min = position;
		this->collider->size = glm::vec2(1, 1);
		this->collider->fixed = true;
	}
}

void Block::update(float dt) {
	if (collider) {
		sprite->position = collider->position_min;
	}
}

} // namespace game
