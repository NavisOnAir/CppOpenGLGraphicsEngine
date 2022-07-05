#pragma once
#include "../../model/shader.h"
#include "../../defines.h"
#include "../../model/indexBuffer.h"
#include "vertex_buffer2d.h"

#include <vector>

namespace gui {

	class Mesh2D {		
	public:
		Mesh2D();
		Mesh2D(std::vector<Vertex2D>& vertices, uint64 numVertices, std::vector<uint32>& indices, uint64 numIndices, Material2D material, Shader* s);
		~Mesh2D();

		// visual
		void render();
		void setMaterial(gui::Material2D nMat);
		gui::Material2D getMaterial();

	private:
		Shader* shader;
		Material2D material;
		VertexBuffer2D* vertexBuffer;
		model::IndexBuffer* indexBuffer;

		uint32 numIndices;
		int colorLocation;
	};
}