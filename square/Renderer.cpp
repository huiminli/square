#include "stdafx.h"
#include "Renderer.h"
#include "GL_Util.h"
#include "Universe.h"

namespace {
	const char *WINDOW_TITLE = "Game of Squares";
	const unsigned SCREEN_WIDTH = 800;
	const unsigned SCREEN_HEIGHT = 600;

	const GLfloat SPRITE_1x1_DATA[] = {
		 0.0f,  0.0f, 0.0f, .0625f,
		32.0f,  0.0f, .0625f, .0625f,
     0.0f, 32.0f, 0.0f, 0.0f,
		32.0f, 32.0f, .0625f, 0.0f,
	};
}

void Renderer::initialize()
{
  SDL_Check(SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE));
  SDL_Check(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4));
  SDL_Check(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1));

	SDL_Check(window.reset(SDL_CreateWindow(
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN)));

	SDL_Check(context.reset(SDL_GL_CreateContext(window.get())));

  glewExperimental = GL_TRUE; // Fix the run-time error in Mac OS.
	GLEW_Check(glewInit());
  glGetError(); // Discard GLEW errors.

	SDL_GL_SetSwapInterval(1);
  glDisable(GL_CULL_FACE);
  glCullFace(GL_BACK);

	loadRamResources();
	loadGpuResources();
}

void Renderer::loadRamResources() {
	SDL_Check(tilesetBitmap.reset(SDL_LoadBMP("mario.bmp")));
	vertexShaderCode = loadFile("vertex.glsl");
	fragmentShaderCode = loadFile("fragment.glsl");
}

void Renderer::loadGpuResources() {
	GL_CHECK(glGenTextures(1, tilesetTexture.getIdPtr()));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, tilesetTexture.getId()));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D,
		0,
    GL_RGB8,
		tilesetBitmap->w,
		tilesetBitmap->h,
		0,
    GL_BGR,
		GL_UNSIGNED_BYTE,
		tilesetBitmap->pixels));

  glGenVertexArrays(1, sprite1x1VA.getIdPtr());
  glBindVertexArray(sprite1x1VA.getId());

  GL_CHECK(glGenBuffers(1, sprite1x1Mesh.getIdPtr()));
  GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, sprite1x1Mesh.getId()));
  GL_CHECK(glBufferData(GL_ARRAY_BUFFER, sizeof(SPRITE_1x1_DATA), SPRITE_1x1_DATA, GL_STATIC_DRAW));
  GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL));
  GL_CHECK(glEnableVertexAttribArray(0));
  GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 4 * sizeof(GLfloat), (GLfloat*) (2 * sizeof(GLfloat))));
  GL_CHECK(glEnableVertexAttribArray(1));

	sprite1x1Shader = compileShader(vertexShaderCode, fragmentShaderCode);
}

void Renderer::render(const Universe &universe)
{
  GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

  GL_CHECK(glUseProgram(sprite1x1Shader.getId()));
  GLint worldPosition = glGetUniformLocation(sprite1x1Shader.getId(), "worldPosition");
  GLint texture2D = glGetUniformLocation(sprite1x1Shader.getId(), "texture2D");

  GL_CHECK(glActiveTexture(GL_TEXTURE0));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, tilesetTexture.getId()));
  GL_CHECK(glUniform1i(texture2D, 0));
  GL_CHECK(glBindVertexArray(sprite1x1VA.getId()));

	for (auto sprite : universe.sprites)
	{
    GL_CHECK(glUniform2f(worldPosition, sprite.x, sprite.y));
    GL_CHECK(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
	}

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    SDL_Log("OpenGL error: %d", err);
  }

	SDL_GL_SwapWindow(window.get());
}

GLProgram Renderer::compileShader(const std::string &vertexShaderCode, std::string fragmentShaderCode)
{
	GLint result = GL_TRUE;
	GLchar errorMessage[4096];

  GL_CHECK(GLShader vertexShader(glCreateShader(GL_VERTEX_SHADER)));
	char const *vertexShaderCodePtr = vertexShaderCode.c_str();
  GL_CHECK(glShaderSource(vertexShader.getId(), 1, &vertexShaderCodePtr, NULL));
  GL_CHECK(glCompileShader(vertexShader.getId()));
  GL_CHECK(glGetShaderiv(vertexShader.getId(), GL_COMPILE_STATUS, &result));
	if (result != GL_TRUE) {
		glGetShaderInfoLog(vertexShader.getId(), sizeof(errorMessage), NULL, errorMessage);
		std::stringstream message; message << "GL error in 'glGetShaderiv': " << errorMessage;
		throw std::runtime_error(message.str().c_str());
	}

  GL_CHECK(GLShader fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
	char const * fragmentShaderCodePtr = fragmentShaderCode.c_str();
  GL_CHECK(glShaderSource(fragmentShader.getId(), 1, &fragmentShaderCodePtr, NULL));
  GL_CHECK(glCompileShader(fragmentShader.getId()));
  GL_CHECK(glGetShaderiv(fragmentShader.getId(), GL_COMPILE_STATUS, &result));
	if (result != GL_TRUE) {
		glGetShaderInfoLog(fragmentShader.getId(), sizeof(errorMessage), NULL, errorMessage);
		std::stringstream message; message << "GL error in 'glGetShaderiv': " << errorMessage;
		throw std::runtime_error(message.str().c_str());
	}

  GL_CHECK(GLProgram program = glCreateProgram());
  GL_CHECK(glAttachShader(program.getId(), vertexShader.getId()));
  GL_CHECK(glAttachShader(program.getId(), fragmentShader.getId()));
  GL_CHECK(glLinkProgram(program.getId()));
  GL_CHECK(glGetProgramiv(program.getId(), GL_LINK_STATUS, &result));
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
