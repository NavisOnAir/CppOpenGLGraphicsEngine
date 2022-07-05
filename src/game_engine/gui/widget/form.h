#pragma once
#include "../../model/shader.h"
#include "../../defines.h"
#include "../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/ext/matrix_transform.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"
#include "../../defines.h"
#include "mesh2d.h"

#include <vector>

namespace gui {
	class Form {
	public:
		Form();
		Form(int screenWidth, int screenHeight, Shader* s, glm::mat4* projectionMatrixptr, int posX, int posY);

		virtual void render();
	protected:
		// positioning
		int x, y;
		int positionLocation;

		// screen
		int screenWidth, screenHeight;
	private:
		// rendering
		Shader* shader;
		glm::mat4* projectionMatrix;
		int projectionLocation;

	};
}