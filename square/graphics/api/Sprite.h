#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace graphics {
	namespace api {

		class Sprite {
		public:
			glm::vec2 position;
			int tileIndex;
		};

	} // namespace api
} // namespace graphics