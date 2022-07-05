#include "mesh2d.h"

namespace gui {
	Mesh2D::Mesh2D() {

	}

	Mesh2D::Mesh2D(std::vector<Vertex2D>& vertices, uint64 numVertices, std::vector<uint32>& indices, uint64 numIndices, Material2D material, Shader* shader) {
		this->material = material;
		this->shader = shader;
		this->numIndices = numIndices;

		shader->bind();
		indexBuffer = new model::IndexBuffer(indices.data(), numIndices, sizeof(indices[0]));
		vertexBuffer = new VertexBuffer2D(vertices.data(), numVertices);
		colorLocation = glGetUniformLocation(shader->getShaderId(), "u_color");
	}

	Mesh2D::~Mesh2D() {
		delete vertexBuffer;
		delete indexBuffer;
	}

	void Mesh2D::render() {
		vertexBuffer->bind();
		indexBuffer->bind();
		glUniform4f(colorLocation, material.color.r, material.color.g, material.color.b, material.color.a);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	}

	void Mesh2D::setMaterial(gui::Material2D nMat) {
		material = nMat;
	}

	gui::Material2D Mesh2D::getMaterial() {
		return material;
	}
}