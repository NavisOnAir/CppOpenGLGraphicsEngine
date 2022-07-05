#include "vertexBuffer.h"

struct Vertex2 {
	float32 x;
	float32 y;
	float32 z;

	float32 r;
	float32 g;
	float32 b;
	float32 a;
};

namespace model {

	VertexBuffer::VertexBuffer(void* data, uint32 numVertices) {
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Daten an GPU senden und speichern an der VAO id (bufferId)
		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), data, GL_STATIC_DRAW);//target, size, data, usage

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(struct Vertex, normal));

		glBindVertexArray(0);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &bufferId);
	}

	void VertexBuffer::bind() {
		glBindVertexArray(vao);
	}

	void VertexBuffer::unbind() {
		glBindVertexArray(0);
	}
}