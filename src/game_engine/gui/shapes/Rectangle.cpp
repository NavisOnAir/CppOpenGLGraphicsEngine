#include "rectangle.h"

namespace gui {
	Rectangle::Rectangle() {
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		shader = nullptr;
	}

	Rectangle::Rectangle(int posX, int posY, float rectWidth, float rectHeight, int screenWidth, int screenHeight, Shader* s, glm::mat4* projectionMatrixptr) : Form(screenWidth, screenHeight, s, projectionMatrixptr, posX, posY) {
		width = rectWidth;
		height = rectHeight;
		shader = s;
		uint64 numVertices;
		std::vector<Vertex2D> vertices;
		uint64 numIndices;
		std::vector<uint32> indices;

		// vertices
		Vertex2D vertex;
		// upper left corner
		vertex.position = { 0, 0 };
		vertices.push_back(vertex);

		// upper right corner
		vertex.position = { width, 0 };
		vertices.push_back(vertex);

		// lower left corner
		vertex.position = { 0, height };
		vertices.push_back(vertex);

		// lower right corner
		vertex.position = { width, height };
		vertices.push_back(vertex);

		// indices
		uint32_t index;
		index = 0;
		indices.push_back(index);
		index = 3;
		indices.push_back(index);
		index = 2;
		indices.push_back(index);
		index = 0;
		indices.push_back(index);
		index = 1;
		indices.push_back(index);
		index = 3;
		indices.push_back(index);

		// material
		Material2D mat;
		mat.color = { 1.0f, 1.0f, 1.0f, 1.0f };

		numVertices = vertices.size();
		numIndices = indices.size();

		// mesh
		rectMesh = new Mesh2D(vertices, numVertices, indices, numIndices, mat, shader);
	}

	void Rectangle::render() {
		shader->bind();
		glUniform2f(positionLocation, x, y);
		rectMesh->render();
	}

	void Rectangle::changeColor(gui::Color nColor) {
		gui::Material2D mat = rectMesh->getMaterial();
		mat.color = nColor;
		rectMesh->setMaterial(mat);
	}

	int Rectangle::updatePosition(int xRel, int yRel) {
		x += xRel;
		y += yRel;

		shader->bind();
		glUniform2f(positionLocation, x, y);

		return 0;
	}
}