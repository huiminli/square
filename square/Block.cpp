#include "stdafx.h"
#include "Block.h"

#include "Collider.h"
#include "EntityFactory.h"
#include "RenderableSprite.h"

Block::Block(EntityFactory& ef, const glm::vec2 &position, const BlockType *blockTemplate)
	: blockTemplate(blockTemplate)
{
	this->sprite = ef.newRenderableSprite();
	this->sprite->position = position;
	this->sprite->tileIndex = blockTemplate->getTileIndex();

	if (blockTemplate->getCollision()) {
		this->collider = ef.newCollider();
		this->collider->position = position;
		this->collider->size = glm::vec2(1, 1);
		this->collider->fixed = true;
	}
}
