#pragma once
#ifndef SQUARE_SDL_UTIL_H
#define SQUARE_SDL_UTIL_H

#define SDL_Check(statement)  \
{ \
  SDL_ClearError(); \
  statement; \
  if (*SDL_GetError()) \
	{ \
    std::stringstream message; message << "SDL error in '" << #statement<< "': " << SDL_GetError(); \
		throw std::runtime_error(message.str().c_str()); \
	} \
}

#define GLEW_Check(statement) \
{ \
  GLenum error = statement; \
  if (GLEW_OK != error) { \
    std::stringstream message; message << "GLEW error in '" << #statement << "': " << glewGetErrorString(error); \
    throw std::runtime_error(message.str().c_str()); \
	} \
}

struct SDL {
public:
	void initialize() {
		SDL_Check(SDL_Init(SDL_INIT_VIDEO));
	}

	~SDL() {
		SDL_Quit();
	}
};

struct SDL_WindowDeleter
{
	void operator()(SDL_Window *window) const
	{
		SDL_DestroyWindow(window);
	}
};

typedef std::unique_ptr<SDL_Window, SDL_WindowDeleter> SDL_WindowPtr;

struct SDL_GLContextDeleter {
	void operator()(SDL_GLContext glContext) const
	{
		SDL_GL_DeleteContext(glContext);
	}
};

typedef std::unique_ptr<void, SDL_GLContextDeleter> SDL_GLContextPtr;

struct SDL_SurfaceDeleter {
	void operator()(SDL_Surface *surface) const
	{
		SDL_FreeSurface(surface);
	}
};

typedef std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter> SDL_SurfacePtr;

#endif SQUARE_SDL_UTIL_H
