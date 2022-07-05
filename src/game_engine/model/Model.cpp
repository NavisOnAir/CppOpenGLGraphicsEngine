#include "model.h"

namespace model {

	void Model::init(const char* filename, Shader* s, float scale, glm::vec3 offset) {
		shader = s;
		// set default pos
		transform = glm::vec3(0.0f, 0.0f, 0.0f);
		model_ = glm::mat4(1.0f);
		model_ = glm::scale(model_, glm::vec3(scale));
		model_ = glm::translate(model_, offset);

		std::ifstream input = std::ifstream(filename, std::ios::in | std::ios::binary);
		uint64 numMeshes = 0;
		if (!input.is_open()) {
			std::cout << "File not found" << std::endl;
		}

#ifdef _DEBUG
		std::cout << "Reading model file..." << std::endl;
#endif

		input.read((char*)&numMeshes, sizeof(uint64));
		this->numMeshes = numMeshes;
#ifdef _DEBUG
		std::cout << "numMeshes: " << numMeshes << std::endl;
#endif

		for (uint64 i = 0; i < numMeshes; i++) {
			Material material;
			std::vector<Vertex> vertices;
			uint64 numVertices = 0;
			std::vector<uint32> indices;
			uint64 numIndices = 0;

			input.read((char*)&material, sizeof(Material));
			input.read((char*)&numVertices, sizeof(uint64));
			input.read((char*)&numIndices, sizeof(uint64));
#ifdef _DEBUG
			std::cout << "numVertices: " << numVertices << std::endl;
			std::cout << "numIndices: " << numIndices << std::endl;
#endif

			for (uint64 i = 0; i < numVertices; i++) {
				Vertex vertex;
				input.read((char*)&vertex.position.x, sizeof(float));
				input.read((char*)&vertex.position.y, sizeof(float));
				input.read((char*)&vertex.position.z, sizeof(float));
				input.read((char*)&vertex.normal.x, sizeof(float));
				input.read((char*)&vertex.normal.y, sizeof(float));
				input.read((char*)&vertex.normal.z, sizeof(float));
				vertices.push_back(vertex);
			}
			for (uint64 i = 0; i < numIndices; i++) {
				uint32 index;
				input.read((char*)&index, sizeof(uint32));
				indices.push_back(index);
			}
			GLuint usage = GL_STATIC_DRAW;
			if (movable) {
				usage = GL_DYNAMIC_DRAW;
			}
			/*
			material.diffuse = { 0.2f, 0.4f, 0.1f };
			material.specular = { 0.0f, 0.0f, 0.0f };
			material.emissive = { 0.0f, 0.0f, 0.0f };
			material.shininess = 0.0f;*/
			Mesh* mesh = new Mesh(vertices, numVertices, indices, numIndices, material, shader);
			meshes.push_back(mesh);
		}
	}

	void Model::init(MeshData* md, float scale, glm::vec3 offset) {
		// set default pos
		transform = glm::vec3(0.0f, 0.0f, 0.0f);
		model_ = glm::mat4(1.0f);
		model_ = glm::scale(model_, glm::vec3(scale));
		model_ = glm::translate(model_, offset);

		Mesh* m = new Mesh(md->getVertices(), md->getNumVertices(), md->getIndices(), md->getNumIndices(), md->getMaterial(), md->getShaderPtr());
		meshes.push_back(m);
	}

	void Model::init(Mesh* m, Shader* s, float scale, glm::vec3 offset) {
		shader = s;
		// set default pos
		transform = glm::vec3(0.0f, 0.0f, 0.0f);
		model_ = glm::mat4(1.0f);
		model_ = glm::scale(model_, glm::vec3(scale));
		model_ = glm::translate(model_, offset);
		meshes.push_back(m);
	}

	void Model::init(Mesh** ms, uint64 numMeshes, Shader* s, float scale, glm::vec3 offset) {
		shader = s;
		// set default pos
		transform = glm::vec3(0.0f, 0.0f, 0.0f);
		model_ = glm::mat4(1.0f);
		model_ = glm::scale(model_, glm::vec3(scale));
		model_ = glm::translate(model_, offset);
		for (int i = 0; i < numMeshes; i++) {
			meshes.push_back(ms[i]);
		}
	}

	void Model::render(glm::mat4 view, glm::mat4 viewProj, int modelViewProjMatrixLocation, int modelViewLocation, int invModelViewLocation) {
		shader->bind();
		glm::mat4 modelViewProj = viewProj * model_;
		glm::mat4 modelView = view * model_;
		glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));

		glUniformMatrix4fv(modelViewProjMatrixLocation, 1, GL_FALSE, &modelViewProj[0][0]);
		glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelView[0][0]);
		glUniformMatrix4fv(invModelViewLocation, 1, GL_FALSE, &invModelView[0][0]);
		for (Mesh* mesh : meshes) {
			mesh->render();
		}
	}

	void Model::move(glm::vec3 moveVector) {
		transform += moveVector;
		model_ = glm::translate(model_, moveVector);
	}

	void Model::printPos() {
		std::cout << "x: " << transform.x << "; y: " << transform.y << "; z: " << transform.z << std::endl;
	}

	Model::~Model() {
		for (Mesh* mesh : meshes) {
			delete mesh;
		}
	}
}