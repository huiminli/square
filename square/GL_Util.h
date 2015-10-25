#pragma once
#ifndef SQUARE_GL_UTIL_H
#define SQUARE_GL_UTIL_H

#include <GL/glew.h>

struct GLShader {
	GLShader(GLuint shaderId) : shaderId(shaderId) {}

	GLuint getId() const {
		return shaderId;
	}

	~GLShader() {
		glDeleteShader(shaderId);
	}
	  
private:
	GLuint shaderId;
};

#endif // SQUARE_GL_UTIL_H