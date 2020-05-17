#pragma once
#include <GL/glew.h>

namespace graphics {

	template<typename Deleter>
	struct GLResource {
		GLResource() : resource(0) {}
		GLResource(GLuint resource) : resource(resource) {}
		GLResource(const GLResource&) = delete;
		// TODO(adrw): Optimize double calls when returning value from a function.
		GLResource(GLResource&& rhs)
		{
			move(std::move(rhs));
		}

		GLResource& operator=(GLResource&& rhs)
		{
			reset();
			move(std::move(rhs));
			return *this;
		};

		~GLResource() {
			reset();
		}

		GLuint getId() const {
			return resource;
		}

		GLuint* getIdPtr() {
			return &resource;
		}

		void reset() {
			if (resource != 0) {
				Deleter d;
				d(resource);
			}

			resource = 0;
		}

	private:
		void move(GLResource&& rhs) {
			resource = rhs.resource;
			rhs.resource = 0;
		}

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

	struct GLTextureDeleter {
		void operator()(GLuint texture) const
		{
			glDeleteTextures(1, &texture);
		}
	};
	typedef GLResource<GLTextureDeleter> GLTexture;

	struct GLVertexArrayDeleter {
		void operator()(GLuint vertexArray) const
		{
			glDeleteVertexArrays(1, &vertexArray);
		}
	};
	typedef GLResource<GLVertexArrayDeleter> GLVertexArray;

}  // namespace graphics
