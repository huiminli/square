#pragma once
#ifndef SQUARE_RENDERABLE_SPRITE_H
#define SQUARE_RENDERABLE_SPRITE_H

class RenderableSprite {
public:
	glm::vec2 position;
	int tileIndex;
	bool fixed;
};

#endif // SQUARE_RENDERABLE_SPRITE_H