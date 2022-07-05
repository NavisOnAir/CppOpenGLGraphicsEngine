#pragma once
#include "../../model/shader.h"
#include "../../../../libs/glm/glm.hpp"
#include "../../../../libs/glm/gtc/type_ptr.hpp"
#include "../../../../libs/glm/ext/matrix_transform.hpp"
#include "../../../../libs/glm/gtc/matrix_transform.hpp"

#include <vector>

namespace gui {
	class UiRenderer {
	private:
		Shader shader;
		
	public:
		UiRenderer();
		UiRenderer(int screenWidth, int screenHeight);
		void add();
		void render();
	};
}