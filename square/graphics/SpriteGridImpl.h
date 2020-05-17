#pragma once
#include "api/SpriteGrid.h"


namespace graphics {
	class SpriteGridImpl : public api::SpriteGrid {
	public:
		bool dirty = true;
		GLTexture tileTexture;
	};
} // namespace graphics 
