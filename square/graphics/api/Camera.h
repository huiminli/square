#pragma once
#include <memory>
#include <glm/glm.hpp>

namespace graphics {
	namespace api {

		class Camera {
		public:
			glm::vec2 position = glm::vec2(0, 0);
		};

	}
} // namespace graphics