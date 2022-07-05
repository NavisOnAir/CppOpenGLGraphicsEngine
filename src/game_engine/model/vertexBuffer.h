#pragma once
#include <GL/glew.h>
#include "../defines.h"

namespace model {

	struct VertexBuffer {
		VertexBuffer(void* data, uint32 numVerteces);
		virtual ~VertexBuffer();
		void bind();
		void unbind();

	private:
		GLuint bufferId;
		GLuint vao;
	};
}