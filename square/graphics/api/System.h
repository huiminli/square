#pragma once
#include <memory>
#include "Camera.h"
#include "Sprite.h"
#include "SpriteGrid.h"

namespace graphics {
	namespace api {

		class System {
		public:
			virtual std::shared_ptr<Sprite> newSprite() = 0;
			virtual SpriteGrid* newSpriteGrid() = 0;
			virtual Camera* getCamera() = 0;
		};

	} // namespace api
} // namespace graphics
