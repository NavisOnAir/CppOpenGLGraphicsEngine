#include "plane.h"

namespace model {
	Plane::Plane(float density, int xSize, int zSize, Shader* s, float scale, glm::vec3 offset) {
		uint64 numVert = (xSize + 1) * (zSize + 1);
		std::vector<Vertex> vertList;
		int i = 0;
		for (int z = 0; z <= zSize; z++) {
			for (int x = 0; x <= xSize; x++) {
				Vertex vertex;
				vertex.position.x = x;
				vertex.position.y = 0;
				vertex.position.z = z;
				vertex.normal.x = x;
				vertex.normal.y = 0;
				vertex.normal.z = z;

				vertList.push_back(vertex);
			}
		}

		uint64 numInd = xSize * xSize * 6;
		std::vector<uint32> indList;
		int vert = 0;
		for (int z = 0; z < zSize; z++) {
			for (int x = 0; x < xSize; x++) {
				indList.push_back(vert + 0);
				indList.push_back(vert + xSize + 1);
				indList.push_back(vert + 1);
				indList.push_back(vert + 1);
				indList.push_back(vert + xSize + 1);
				indList.push_back(vert + xSize + 2);
				vert++;
			}
		}

		Material mat;
		mat.diffuse = { 1.0f, 1.0f, 1.0f };
		mat.specular = { 0.0f, 0.0f, 0.0f };
		mat.emissive = { 0.0f, 0.0f, 0.0f };
		mat.shininess = 0.0f;

		MeshData md(vertList, numVert, indList, numInd, mat, s);

		mModel = new Model();
		mModel->init(&md, scale, glm::vec3(0.0f));
	}

	Plane::~Plane() {
		delete(mModel);
	}

	Model* Plane::getModelPtr() {
		return mModel;
	}

	void Plane::render(glm::mat4 view, glm::mat4 viewProj, int modelViewMatrixLocation, int modelViewLocation, int invModelViewLocation) {
		mModel->render(view, viewProj, modelViewMatrixLocation, modelViewLocation, invModelViewLocation);
	}
}