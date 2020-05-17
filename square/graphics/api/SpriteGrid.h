#pragma once
#include <memory>
#include <vector>
#include <glm/glm.hpp>

namespace graphics {
	namespace api {

		class SpriteGrid {
		public:
			glm::vec2 position;
			std::vector<unsigned char> tiles;
			int width;
			int height;

			// TODO: getters and setters.

		};

	} // namespace api
} // namespace graphics