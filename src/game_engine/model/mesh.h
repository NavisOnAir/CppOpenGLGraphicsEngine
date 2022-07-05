#pragma once
#include "../../../libs/glm/glm.hpp"
#include"../../../libs/glm/ext/matrix_transform.hpp"
#include"../../../libs/glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include <vector>
#include <fstream>
#include "../defines.h"

namespace model {

	class Mesh {
	public:
		Mesh();
		Mesh(std::vector<Vertex>& vertices, uint64 numVertices, std::vector<uint32>& indices, uint64 numIndices, Material material, Shader* shader);
		~Mesh();
		void render();
	private:
		VertexBuffer* vertexBuffer;
		IndexBuffer* indexBuffer;
		Shader* shader;
		Material material;
		//std::vector<uint32> indices;
		//std::vector<Vertex> vertices;
		uint64 numIndices = 0;
		//uint64 numVertices = 0;
		int diffuseLocation;
		int specularLocation;
		int emissiveLocation;
		int shininessLocation;

		void modifyVertPos(Vertex* vert, Transform trans);
	};
}