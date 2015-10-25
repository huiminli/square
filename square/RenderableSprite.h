#pragma once
#ifndef SQUARE_RENDERABLE_SPRITE_H
#define SQUARE_RENDERABLE_SPRITE_H

enum class SpriteType : unsigned char {
	A,
	B,
	C
};

struct RenderableSprite {
	float x, y, w, h;
	SpriteType type;
};

#endif // SQUARE_RENDERABLE_SPRITE_H