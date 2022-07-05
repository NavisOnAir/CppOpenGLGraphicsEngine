#pragma once
#include "../../defines.h"

namespace gui {
	class VertexBuffer2D {
	public:
		VertexBuffer2D(void* data, uint32 numVertices);
		~VertexBuffer2D();
		void bind();
		void unbind();
	private:
		GLuint bufferId;
		GLuint vao;
	};
}