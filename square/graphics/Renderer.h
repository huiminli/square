#pragma once
#include <list>
#include "../common/SDL_Util.h"
#include "api/Camera.h"
#include "api/Sprite.h"
#include "api/SpriteGrid.h"
#include "api/System.h"
#include "GL_Util.h"
#include "SpriteGridImpl.h"

namespace graphics {
	class Renderer : public ::graphics::api::System {
	public:
		void initialize();
		void render();

		std::shared_ptr<api::Sprite> newSprite() override;
		api::SpriteGrid* newSpriteGrid() override;
		api::Camera* getCamera() override;

	private:
		void renderSpriteGrids(glm::mat4& worldToScreen);
		void renderSprites(glm::mat4& worldToScreen);

		void loadResources();
		static GLProgram compileShader(const char* vertexFile, const char* fragmentFile);
		static std::string loadFile(const char* file);

	private: // Rendering entities.
		api::Camera camera;
		std::list<std::weak_ptr<api::Sprite>> sprites;
		std::list<std::unique_ptr<SpriteGridImpl>> spriteGrids;

	private: // Device.
		SDL_WindowPtr window;
		SDL_GLContextPtr context;

	private: // GPU resources.
		GLTexture tilesetTexture;

		GLProgram spriteShader;
		GLProgram spriteGridShader;
		GLVertexArray quadVA;
		GLBuffer quadBuffer;
	};

} // namespace graphics