#include "vertex_buffer2d.h"

namespace gui {
	VertexBuffer2D::VertexBuffer2D(void* data, uint32 numVertices) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex2D), data, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(struct Vertex2D, position));

		glBindVertexArray(0);
	}

	VertexBuffer2D::~VertexBuffer2D() {
		glDeleteBuffers(1, &bufferId);
	}

	void VertexBuffer2D::bind() {
		glBindVertexArray(vao);
	}

	void VertexBuffer2D::unbind() {
		glBindVertexArray(0);
	}
}