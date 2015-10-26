#include "stdafx.h"
#include "Renderer.h"
#include "GL_Util.h"
#include "Universe.h"

namespace {
	const char *WINDOW_TITLE = "Game of Squares";
	const unsigned SCREEN_WIDTH = 800;
	const unsigned SCREEN_HEIGHT = 600;

	const GLfloat SPRITE_1x1_DATA[] = {
		 0.0f,   0.0f, 0.0f, 0.0f,
		 0.0f,  32.0f, 0.0f, 1.0f,
		32.0f,   0.0f, 1.0f, 0.0f,
		32.0f,  32.0f, 1.0f, 1.0f,
	};
}

void Renderer::initialize()
{
  
  SDL_Check(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE));
  SDL_Check(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3));
  SDL_Check(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3));
  
	SDL_Check(window.reset(SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)));

	SDL_Check(context.reset(SDL_GL_CreateContext(window.get())));
	GLEW_Check(glewInit());

	SDL_GL_SetSwapInterval(1);
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
	glGenTextures(1, tilesetTexture.getIdPtr());
	glBindTexture(GL_TEXTURE_2D, tilesetTexture.getId());
	glTexImage2D(GL_TEXTURE_2D,
		0,
		tilesetBitmap->format->BytesPerPixel,
		tilesetBitmap->w,
		tilesetBitmap->h,
		0,
		GL_BGR,
		GL_UNSIGNED_BYTE,
		tilesetBitmap->pixels);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, sprite1x1Mesh.getIdPtr());
	glBindBuffer(GL_ARRAY_BUFFER, sprite1x1Mesh.getId());
	glBufferData(GL_ARRAY_BUFFER, sizeof(SPRITE_1x1_DATA), SPRITE_1x1_DATA, GL_STATIC_DRAW);

	sprite1x1Shader = compileShader(vertexShaderCode, fragmentShaderCode);

  glGenSamplers(1, linearSampler.getIdPtr());
  glSamplerParameteri(linearSampler.getId(), GL_TEXTURE_WRAP_S, GL_REPEAT);
  glSamplerParameteri(linearSampler.getId(), GL_TEXTURE_WRAP_T, GL_REPEAT);
  glSamplerParameteri(linearSampler.getId(), GL_TEXTURE_WRAP_R, GL_REPEAT);
  glSamplerParameteri(linearSampler.getId(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glSamplerParameteri(linearSampler.getId(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glSamplerParameteri(linearSampler.getId(), GL_TEXTURE_MAX_ANISOTROPY_EXT, 16);
}

void Renderer::render(const Universe &universe)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(sprite1x1Shader.getId());

  GLint texture2D = glGetUniformLocation(sprite1x1Shader.getId(), "texture2D");
  GLint worldPosition = glGetUniformLocation(sprite1x1Shader.getId(), "worldPosition");

  glUniform1i(texture2D, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tilesetTexture.getId());
  glBindSampler(0, linearSampler.getId());

	glBindBuffer(GL_ARRAY_BUFFER, sprite1x1Mesh.getId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));

	for (auto sprite : universe.sprites)
	{
		glUniform2f(worldPosition, sprite.x, sprite.y);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
  glBindTexture(GL_TEXTURE_2D, 0);

	SDL_GL_SwapWindow(window.get());
}

GLProgram Renderer::compileShader(const std::string &vertexShaderCode, std::string fragmentShaderCode)
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
		glGetShaderInfoLog(fragmentShader.getId(), sizeof(errorMessage), NULL, errorMessage);
		std::stringstream message; message << "GL error in 'glGetShaderiv': " << errorMessage;
		throw std::runtime_error(message.str().c_str());
	}

	GLProgram program = glCreateProgram();
	glAttachShader(program.getId(), vertexShader.getId());
	glAttachShader(program.getId(), fragmentShader.getId());
	glLinkProgram(program.getId());
	glGetProgramiv(program.getId(), GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		glGetProgramInfoLog(program.getId(), sizeof(errorMessage), NULL, errorMessage);
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
