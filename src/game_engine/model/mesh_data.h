#pragma once
#include "../defines.h"
#include "shader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"

#include <vector>

namespace model {
	class MeshData {
	public:
		MeshData(std::vector<Vertex>& vertices, uint64 numVertices, std::vector<uint32>& indices, uint64 numIndices, Material material, Shader* shader);
		std::vector<Vertex>& getVertices();
		std::vector<uint32>& getIndices();
		uint64 getNumVertices();
		uint64 getNumIndices();
		Material getMaterial();
		Shader* getShaderPtr();


	private:
		std::vector<Vertex> mvertices;
		std::vector<uint32> mindices;
		uint64 mnumVertices;
		uint64 mnumIndices;
		Material mmaterial;
		Shader* mpshader;
	};
}

