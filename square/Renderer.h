#pragma once
#ifndef SQUARE_RENDEDRER_H
#define SQUARE_RENDEDRER_H

#include "SDL_Util.h"

class Universe;

class Renderer {
public:
	~Renderer();

	void initialize();
	void render(const Universe &universe);

private:
	void loadRamResources();
	void loadGpuResources();
	static GLuint compileShader(const std::string &vertexShader, std::string fragmentShader);
	static std::string loadFile(const char *file);

private: // Device.
	SDL_WindowPtr window;
	SDL_GLContextPtr context;

private: // RAM resources.
	SDL_SurfacePtr tilesetBitmap;
	std::string vertexShaderCode;
	std::string fragmentShaderCode;

private: // GPU resources.
	GLuint tilesetTexture;
	GLuint sprite1x1Mesh;
	GLuint sprite1x1Shader;
};

#endif // SQUARE_RENDEDRER_H