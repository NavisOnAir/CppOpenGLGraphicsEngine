#pragma once
#include "../shader.h"
#include "../model.h"
#include "../mesh_data.h"
#include "../../defines.h"

namespace model {
	class Plane {
	public:
		Plane(float density, int xSize, int zSize, Shader* s, float scale, glm::vec3 offset);
		~Plane();
		Model* getModelPtr();
		void render(glm::mat4 view, glm::mat4 viewProj, int modelViewMatrixLocation, int modelViewLocation, int invModelViewLocation);

	private:
		model::Model* mModel;
	};
}