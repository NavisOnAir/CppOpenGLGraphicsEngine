#include "form.h"

namespace gui {
	Form::Form() {

	}

	Form::Form(int screenWidth, int screenHeight, Shader* s, glm::mat4* projectionMatrixptr, int posX, int posY) {
		screenWidth = screenWidth;
		screenHeight = screenHeight;
		shader = s;
		x = posX;
		y = posY;

		shader->bind();
		projectionMatrix = projectionMatrixptr;
		projectionLocation = glGetUniformLocation(shader->getShaderId(), "u_projection");
		positionLocation = glGetUniformLocation(shader->getShaderId(), "u_position");
		std::cout << "x: " << x << " y: " << y << std::endl;
		glUniform2f(positionLocation, x, y);
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(*projectionMatrix));
	}

	void Form::render() {

	}
}