#pragma once
#ifndef SQUARE_RENDEDRER_H
#define SQUARE_RENDEDRER_H

#include "SDL_Util.h"
#include "GL_Util.h"

class Universe;

class Renderer {
public:
	void initialize();
	void render(const Universe &universe);

private:
	void renderBackground(const Universe &universe, glm::mat4 &worldToScreen);
	void renderSprites(const Universe &universe, glm::mat4 &worldToScreen);

	void loadResources();
	static GLProgram compileShader(const char *vertexFile, const char *fragmentFile);
	static std::string loadFile(const char *file);

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