#pragma once
#ifndef SQUARE_GL_UTIL_H
#define SQUARE_GL_UTIL_H

#include <GL/glew.h>

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
		glDeleteBuffers(1, &buffer);
	}
};
typedef GLResource<GLBufferDeleter> GLBuffer;

struct GLShaderDeleter {
	void operator()(GLuint shader) const 
	{
		glDeleteShader(shader);
	}
};
typedef GLResource<GLShaderDeleter> GLShader;

struct GLProgramDeleter {
	void operator()(GLuint progam) const
	{
		glDeleteProgram(progam);
	}
};
typedef GLResource<GLProgramDeleter> GLProgram;

struct GLSamplerDeleter {
  void operator()(GLuint sampler) const
  {
    glDeleteSamplers(1, &sampler);
  }
};
typedef GLResource<GLSamplerDeleter> GLSampler;

struct GLTextureDeleter {
	void operator()(GLuint texture) const
	{
		glDeleteTextures(1, &texture);
	}
};
typedef GLResource<GLTextureDeleter> GLTexture;

#endif // SQUARE_GL_UTIL_H