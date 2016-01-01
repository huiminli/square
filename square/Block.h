#pragma once
#ifndef SQUARE_BLOCK_H
#define SQUARE_BLOCK_H

#include <memory>
#include "Entity.h"

class Collider;
class EntityFactory;
class RenderableSprite;

class BlockType {
public:
	BlockType(unsigned tileIndex, bool collision) : tileIndex(tileIndex), collision(collision) {}

	unsigned getTileIndex() const { return tileIndex; }
	bool getCollision() const { return collision; }

private: 
	const unsigned tileIndex;
	const bool collision;
};

class Block : public Entity {
public:
	Block(EntityFactory &ef, const glm::vec2 &position, const BlockType *blockTemplate);

private:
	const BlockType *blockTemplate;
	std::shared_ptr<RenderableSprite> sprite;
	std::shared_ptr<Collider> collider;
};

#endif // SQUARE_BLOCK_H