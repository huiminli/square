#pragma once
#ifndef SQUARE_UNIVERSE_H
#define SQUARE_UNIVERSE_H

#include <list>
#include "EntityFactory.h"
#include "RenderableSprite.h"
#include "Player.h"

class Universe : public EntityFactory {
public:
	void update(float dt);
  std::list<std::weak_ptr<RenderableSprite>> getSprites() const;

	bool upPressed = false;
	bool downPressed = false;
	bool leftPressed = false;
	bool rightPressed = false;
	std::unique_ptr<Player> mPlayer;

	virtual std::shared_ptr<RenderableSprite> newRenderableSprite() override;

private:
	std::list<std::weak_ptr<RenderableSprite>> sprites;
};

#endif // SQUARE_UNIVERSE_H