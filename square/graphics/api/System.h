#pragma once
#include <memory>
#include "Camera.h"
#include "Sprite.h"

namespace graphics {
	namespace api {

		class System {
		public:
			virtual std::shared_ptr<Sprite> newRenderableSprite() = 0;
			virtual Camera* getCamera() = 0;
		};

	} // namespace api
} // namespace graphics
