#pragma once
#ifndef SQUARE_GL_UTIL_H
#define SQUARE_GL_UTIL_H

#include <GL/glew.h>

#define GL_CHECK(statement) \
  statement; \
  { \
    GLenum error = glGetError(); \
    if (error != GL_NO_ERROR) { \
      SDL_Log("OpenGL error %d in %s", error, #statement); \
    } \
  }

template<typename Deleter>
struct GLResource {
	GLResource() : resource(0) {}
	GLResource(GLuint resource) : resource(resource) {}
	GLResource(const GLResource&) = delete;
	// TODO(adrw): Optimize double calls when returning value from a function.
	GLResource(GLResource &&rhs) { *this = std::move(rhs); }
	GLResource& operator=(GLResource &&rhs)
	{
		glDeleteProgram(resource);
		resource = rhs.resource;
		rhs.resource = 0;
		return *this;
	};

	GLuint getId() const {
		return resource;
	}

	GLuint* getIdPtr() {
		return &resource;
	}

	~GLResource() {
		Deleter d;
		d(resource);
	}

private:
	GLuint resource;
};

struct GLBufferDeleter {
	void operator()(GLuint buffer) const
	{
    GL_CHECK(glDeleteBuffers(1, &buffer));
	}
};
typedef GLResource<GLBufferDeleter> GLBuffer;

struct GLShaderDeleter {
	void operator()(GLuint shader) const 
	{
    GL_CHECK(glDeleteShader(shader));
	}
};
typedef GLResource<GLShaderDeleter> GLShader;

struct GLProgramDeleter {
	void operator()(GLuint progam) const
	{
    GL_CHECK(glDeleteProgram(progam));
	}
};
typedef GLResource<GLProgramDeleter> GLProgram;

struct GLTextureDeleter {
	void operator()(GLuint texture) const
	{
    GL_CHECK(glDeleteTextures(1, &texture));
	}
};
typedef GLResource<GLTextureDeleter> GLTexture;

#endif // SQUARE_GL_UTIL_H