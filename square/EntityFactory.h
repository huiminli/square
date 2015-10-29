#pragma once
#ifndef SQUARE_ENTITY_FACTORY
#define SQUARE_ENTITY_FACTORY

class RenderableSprite;

class Camera {
public:
	float x = 0.0f;
	float y = 0.0f;
};

class EntityFactory {
public:
	virtual std::shared_ptr<RenderableSprite> newRenderableSprite() = 0;
	virtual Camera* getCamera() = 0;
};

#endif // SQUARE_ENTITY_FACTORY