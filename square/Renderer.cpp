#include "stdafx.h"
#include "Renderer.h"
#include "GL_Util.h"
#include "Universe.h"

namespace {
	const char *WINDOW_TITLE = "Game of Squares";
	const unsigned SCREEN_WIDTH = 800;
	const unsigned SCREEN_HEIGHT = 600;
	const float TILE_SIZE = 32.0f;

	const GLfloat SPRITE_1x1_DATA[] = {
		 0.0f, 0.0f,
		 1.0f, 0.0f,
     0.0f, 1.0f,
		 1.0f, 1.0f,
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

	// TODO(adrw): Do not include GLEW on platforms different that Windows.
  glewExperimental = GL_TRUE; // Fix the run-time error in Mac OS.
	GLEW_Check(glewInit());
  glGetError(); // Discard GLEW errors.

	SDL_GL_SetSwapInterval(1);
  glDisable(GL_CULL_FACE);
  glCullFace(GL_BACK);

	loadResources();
}

void Renderer::loadResources() {
	SDL_SurfacePtr tilesetBitmap;
	SDL_Check(tilesetBitmap.reset(SDL_LoadBMP("mario.bmp")));

	glGenTextures(1, tilesetTexture.getIdPtr());
  glBindTexture(GL_TEXTURE_2D, tilesetTexture.getId());
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB8,
			tilesetBitmap->w,
			tilesetBitmap->h,
			0,
			GL_BGR,
			GL_UNSIGNED_BYTE,
			tilesetBitmap->pixels);

  glGenVertexArrays(1, quadVA.getIdPtr());
  glBindVertexArray(quadVA.getId());

  glGenBuffers(1, quadBuffer.getIdPtr());
  glBindBuffer(GL_ARRAY_BUFFER, quadBuffer.getId());
  glBufferData(GL_ARRAY_BUFFER, sizeof(SPRITE_1x1_DATA), SPRITE_1x1_DATA, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	spriteShader = compileShader("sprite.vert", "sprite.frag");

	//glGenTextures(1, backgroundTilesTexture.getIdPtr());
	//glBindTexture(GL_TEXTURE_2D, backgroundTilesTexture.getId());
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexImage2D(
	//		GL_TEXTURE_2D,
	//		0,
	//		GL_R8UI,
	//		BACKGROUND_SIZE,
	//		BACKGROUND_SIZE,
	//		0,
	//		GL_RED_INTEGER,
	//		GL_UNSIGNED_BYTE,
	//		BACKGROUND_TILES);

	//backgroundShader = compileShader("background.vert", "background.frag");
}

void Renderer::render(const Universe &universe)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 cameraMatrix = glm::mat4(
		1.0f, 0.0f, 0.0f, -universe.getCamera()->x * TILE_SIZE,
		0.0f, 1.0f, 0.0f, -universe.getCamera()->y * TILE_SIZE,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 projectionMatrix = glm::mat4(
		2.0f / SCREEN_WIDTH, 0.0f, 0.0f, -1.0f,
		0.0f, 2.0f / SCREEN_HEIGHT, 0.0f, -1.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 worldToScreen = cameraMatrix * projectionMatrix;

	// renderBackground(universe, worldToScreen);
	renderSprites(universe, worldToScreen);

  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    SDL_Log("OpenGL error: %d", err);
  }

	SDL_GL_SwapWindow(window.get());
}

//void Renderer::renderBackground(const Universe &universe, glm::mat4 &worldToScreen)
//{
//	glUseProgram(backgroundShader.getId());
//	GLint uWorldToScreen = glGetUniformLocation(backgroundShader.getId(), "worldToScreen");
//	GLint uBackgorundSize = glGetUniformLocation(backgroundShader.getId(), "backgorundSize");
//	GLint uTileTexture = glGetUniformLocation(backgroundShader.getId(), "tileTexture");
//	GLint uBackgroundTilesTexture = glGetUniformLocation(backgroundShader.getId(), "backgroundTilesTexture");
//
//	glBindVertexArray(quadVA.getId());
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, tilesetTexture.getId());
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, backgroundTilesTexture.getId());
//
//	glUniformMatrix4fv(uWorldToScreen, 1, false, &worldToScreen[0][0]);
//	glUniform2f(uBackgorundSize, (float) BACKGROUND_SIZE, (float) BACKGROUND_SIZE);
//	glUniform1i(uTileTexture, 0);
//	glUniform1i(uBackgroundTilesTexture, 1);
//
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//}

void Renderer::renderSprites(const Universe &universe, glm::mat4 &worldToScreen)
{
	glUseProgram(spriteShader.getId());
	GLint uWorldPosition = glGetUniformLocation(spriteShader.getId(), "worldPosition");
	GLint uWorldToScreen = glGetUniformLocation(spriteShader.getId(), "worldToScreen");
	GLint uTileIndex = glGetUniformLocation(spriteShader.getId(), "tileIndex");
	GLint uTileTexture = glGetUniformLocation(spriteShader.getId(), "tileTexture");

	glBindVertexArray(quadVA.getId());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tilesetTexture.getId());

	glUniformMatrix4fv(uWorldToScreen, 1, false, &worldToScreen[0][0]);
	glUniform1i(uTileTexture, 0);
	for (auto &sprite_weak : universe.getRenderableSprites())
	{
		if (auto sprite = sprite_weak.lock()) {
			glUniform2f(uWorldPosition, sprite->position.x, sprite->position.y);
			glUniform1ui(uTileIndex, sprite->tileIndex);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}
	}
}

GLProgram Renderer::compileShader(const char *vertexFile, const char *fragmentFile)
{
	GLint result = GL_TRUE;
	GLchar errorMessage[4096];

	std::string vertexCode = loadFile(vertexFile);
	std::string fragmentCode = loadFile(fragmentFile);

  GLShader vertexShader(glCreateShader(GL_VERTEX_SHADER));
	char const *vertexCodePtr = vertexCode.c_str();
  glShaderSource(vertexShader.getId(), 1, &vertexCodePtr, NULL);
  glCompileShader(vertexShader.getId());
  glGetShaderiv(vertexShader.getId(), GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		glGetShaderInfoLog(vertexShader.getId(), sizeof(errorMessage), NULL, errorMessage);
		std::stringstream message; message << "GL error in 'glGetShaderiv': " << errorMessage;
		throw std::runtime_error(message.str().c_str());
	}

  GLShader fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	char const * fragmentCodePtr = fragmentCode.c_str();
  glShaderSource(fragmentShader.getId(), 1, &fragmentCodePtr, NULL);
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
