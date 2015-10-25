#include "stdafx.h"
#include "Renderer.h"
#include "GL_Util.h"

namespace {
	const char *WINDOW_TITLE = "Game of Squares";
	const unsigned SCREEN_WIDTH = 800;
	const unsigned SCREEN_HEIGHT = 600;
	const unsigned UNIVERSE_TICK_MS = 10;

	const GLfloat SPRITE_1x1_DATA[] = {
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
		1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
	};
}

Renderer::~Renderer() {
	glDeleteTextures(1, &tilesetTexture);
	glDeleteBuffers(1, &sprite1x1Mesh);
	glDeleteProgram(sprite1x1Shader);
}

void Renderer::initialize()
{
	// Set GL attributes _before_ creating the window.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_Check(window.reset(SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)));

	SDL_Check(context.reset(SDL_GL_CreateContext(window.get())));
	GLEW_Check(glewInit());

	glEnable(GL_TEXTURE_2D);

	loadRamResources();
	loadGpuResources();
}

void Renderer::loadRamResources() {
	SDL_Check(tilesetBitmap.reset(SDL_LoadBMP("mario.bmp")));
	vertexShaderCode = loadFile("vertex.glsl");
	fragmentShaderCode = loadFile("fragment.glsl");
}

void Renderer::loadGpuResources() {
	// TODO(adrw): Release.
	glGenTextures(1, &tilesetTexture);
	glBindTexture(GL_TEXTURE_2D, tilesetTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		tilesetBitmap->format->BytesPerPixel,
		tilesetBitmap->w,
		tilesetBitmap->h,
		0,
		GL_BGR,
		GL_UNSIGNED_BYTE,
		tilesetBitmap->pixels);

	glGenBuffers(1, &sprite1x1Mesh);
	glBindBuffer(GL_ARRAY_BUFFER, sprite1x1Mesh);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SPRITE_1x1_DATA), SPRITE_1x1_DATA, GL_STATIC_DRAW);

	// TODO(adrw): Release.
	sprite1x1Shader = compileShader(vertexShaderCode, fragmentShaderCode);
}

void Renderer::render(const Universe & universe)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw the player sprite.
	glUseProgram(sprite1x1Shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tilesetTexture);
	glUniform1i(0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, sprite1x1Mesh);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (const GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);


	SDL_GL_SwapWindow(window.get());
}

GLuint Renderer::compileShader(const std::string &vertexShaderCode, std::string fragmentShaderCode)
{
	GLint result = GL_TRUE;
	GLchar errorMessage[4096];

	GLShader vertexShader(glCreateShader(GL_VERTEX_SHADER));
	char const *vertexShaderCodePtr = vertexShaderCode.c_str();
	glShaderSource(vertexShader.getId(), 1, &vertexShaderCodePtr, NULL);
	glCompileShader(vertexShader.getId());
	glGetShaderiv(vertexShader.getId(), GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		glGetShaderInfoLog(vertexShader.getId(), sizeof(errorMessage), NULL, errorMessage);
		std::stringstream message; message << "GL error in 'glGetShaderiv': " << errorMessage;
		throw std::runtime_error(message.str().c_str());
	}

	GLShader fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	char const * fragmentShaderCodePtr = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader.getId(), 1, &fragmentShaderCodePtr, NULL);
	glCompileShader(fragmentShader.getId());
	glGetShaderiv(fragmentShader.getId(), GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		std::stringstream message; message << "GL error in 'glGetShaderiv': " << errorMessage;
		throw std::runtime_error(message.str().c_str());
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader.getId());
	glAttachShader(program, fragmentShader.getId());
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		glGetProgramInfoLog(program, sizeof(errorMessage), NULL, errorMessage);
		std::stringstream message; message << "GL error in 'glGetShaderiv': " << errorMessage;
		throw std::runtime_error(message.str().c_str());
	}

	return program;
}

std::string Renderer::loadFile(const char *file) {
	std::ifstream stream(file, std::ios::in);
	if (stream.fail()) {
		std::stringstream message; message << "System error in 'ifstream': " << strerror(errno);
		throw std::runtime_error(message.str().c_str());
	}

	std::ostringstream output;
	output << stream.rdbuf();
	if (stream.fail()) {
		std::stringstream message; message << "System error in 'ifstream': " << strerror(errno);
		throw std::runtime_error(message.str().c_str());
	}

	return output.str();
}
