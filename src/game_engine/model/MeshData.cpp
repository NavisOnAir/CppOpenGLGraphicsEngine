#include "mesh_data.h"

namespace model {
	MeshData::MeshData(std::vector<Vertex>& vertices, uint64 numVertices, std::vector<uint32>& indices, uint64 numIndices, Material material, Shader* shader) {
		mvertices = vertices;
		mnumVertices = numVertices;
		mindices = indices;
		mnumIndices = numIndices;
		mmaterial = material;
		mpshader = shader;
	}
	std::vector<Vertex>& MeshData::getVertices() {
		return mvertices;
	}

	std::vector<uint32>& MeshData::getIndices() {
		return mindices;
	}

	uint64 MeshData::getNumVertices() {
		return mnumVertices;
	}

	uint64 MeshData::getNumIndices() {
		return mnumIndices;
	}

	Material MeshData::getMaterial() {
		return mmaterial;
	}

	Shader* MeshData::getShaderPtr() {
		return mpshader;
	}

}