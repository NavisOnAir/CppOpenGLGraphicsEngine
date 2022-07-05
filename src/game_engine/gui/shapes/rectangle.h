#pragma once
#include "../widget/mesh2d.h"
#include "../widget/form.h"


namespace gui {
	class Rectangle : public gui::Form {
	public:
		Rectangle();
		Rectangle(int posX, int posY, float rectWidth, float rectHeight, int screenWidth, int screenHeight, Shader* s, glm::mat4* projectionMatrixptr);
	
		// visual
		virtual void render();
		void changeColor(gui::Color nColor);
		int updatePosition(int xRel, int yRel);
	private:
		float width, height;
		Shader* shader;
		gui::Mesh2D* rectMesh;
	};
}