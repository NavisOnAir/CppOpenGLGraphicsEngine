#pragma once
#include "shader.h"
#include <vector>
#include "mesh.h"
#include "mesh_data.h"
#include "../defines.h"

namespace model {

	class Model {
	public:
		void init(const char* filename, Shader* s, float scale, glm::vec3 offset);
		void init(MeshData* md, float scale, glm::vec3 offset);
		void init(Mesh* m, Shader* s, float scale, glm::vec3 offset);
		void init(Mesh** ms, uint64 numMeshes, Shader* s, float scale, glm::vec3 offset);
		void render(glm::mat4 view, glm::mat4 viewProj, int modelViewProjMatrixLocation, int modelViewLocation, int invModelViewLocation);
		void move(glm::vec3 moveVector);
		void printPos();
		~Model();
	private:
		std::vector<Mesh*> meshes;
		uint64 numMeshes;
		glm::mat4 model_;
		glm::vec3 transform;
		glm::vec3 offset;
		bool movable;
		Shader* shader;
	};
}