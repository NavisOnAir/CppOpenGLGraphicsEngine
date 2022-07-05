#pragma once
#include <GL/glew.h>
#include "../defines.h"

namespace model {

	struct IndexBuffer {
		IndexBuffer(void* data, uint32 numIndices, uint8 elementSize);
		virtual ~IndexBuffer();
		void bind();
		void unbind();

	private:
		GLuint bufferId;
	};
}