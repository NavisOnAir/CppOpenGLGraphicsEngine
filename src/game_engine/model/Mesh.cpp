#include "mesh.h"

namespace model {

	Mesh::Mesh() {

	}

	Mesh::Mesh(std::vector<Vertex>& vertices, uint64 numVertices, std::vector<uint32>& indices, uint64 numIndices, Material material, Shader* shader) {
		this->material = material;
		this->shader = shader;
		this->numIndices = numIndices;
		//this->numVertices = numVertices;
		//this->indices = indices;
		//this->vertices = vertices;

		indexBuffer = new IndexBuffer(indices.data(), numIndices, sizeof(indices[0]));
		vertexBuffer = new VertexBuffer(vertices.data(), numVertices);
		diffuseLocation = glGetUniformLocation(shader->getShaderId(), "u_material.diffuse");
		specularLocation = glGetUniformLocation(shader->getShaderId(), "u_material.specular");
		emissiveLocation = glGetUniformLocation(shader->getShaderId(), "u_material.emissive");
		shininessLocation = glGetUniformLocation(shader->getShaderId(), "u_material.shininess");

	}

	Mesh::~Mesh() {
		delete vertexBuffer;
		delete indexBuffer;
	}

	void Mesh::render() {

		vertexBuffer->bind();
		indexBuffer->bind();
		glUniform3fv(diffuseLocation, 1, (float*)&material.diffuse);
		glUniform3fv(specularLocation, 1, (float*)&material.specular);
		glUniform3fv(emissiveLocation, 1, (float*)&material.emissive);
		glUniform1f(shininessLocation, material.shininess);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	}

	void Mesh::modifyVertPos(Vertex* vert, Transform trans) {
		vert->position.x += trans.x;
		vert->position.y += trans.y;
		vert->position.z += trans.z;
	}
}