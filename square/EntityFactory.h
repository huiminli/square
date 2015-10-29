#pragma once
#ifndef SQUARE_ENTITY_FACTORY
#define SQUARE_ENTITY_FACTORY

class RenderableSprite;

class EntityFactory {
public:
	virtual std::shared_ptr<RenderableSprite> newRenderableSprite() = 0;
};

#endif // SQUARE_ENTITY_FACTORY