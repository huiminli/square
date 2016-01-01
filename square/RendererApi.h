#pragma once
#ifndef SQUARE_RENDER_API_H
#define SQUARE_RENDER_API_H

#include <memory>
#include <glm/glm.hpp>

class Camera {
public:
	glm::vec2 position = glm::vec2(0, 0);
};

class RenderableSprite {
public:
	glm::vec2 position;
	int tileIndex;
	bool fixed;
};

class RendererFactory {
public:
	virtual std::shared_ptr<RenderableSprite> newRenderableSprite() = 0;
	virtual Camera* getCamera() = 0;
};

#endif // SQUARE_RENDER_API_H