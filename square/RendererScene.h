#pragma once
#ifndef SQUARE_RENDEDRER_H
#define SQUARE_RENDEDRER_H

#include <list>
#include "SDL_Util.h"
#include "GL_Util.h"
#include "RendererApi.h"

class Universe;

class RendererScene : public RendererFactory {
public:
	void initialize();
	void render();

	std::shared_ptr<RenderableSprite> newRenderableSprite() override;
	Camera* getCamera() override;

private:
	//void renderBackground(glm::mat4 &worldToScreen);
	void renderSprites(glm::mat4 &worldToScreen);

	void loadResources();
	static GLProgram compileShader(const char *vertexFile, const char *fragmentFile);
	static std::string loadFile(const char *file);

private: // Rendering entities.
	Camera camera;
	std::list<std::weak_ptr<RenderableSprite>> sprites;

private: // Device.
	SDL_WindowPtr window;
	SDL_GLContextPtr context;

private: // GPU resources.
	GLTexture tilesetTexture;

	GLProgram spriteShader;
	GLVertexArray quadVA;
	GLBuffer quadBuffer;

	//GLTexture backgroundTilesTexture;
	//GLProgram backgroundShader;
};

#endif // SQUARE_RENDEDRER_H