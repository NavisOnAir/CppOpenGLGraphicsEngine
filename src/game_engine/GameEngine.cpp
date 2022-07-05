#include "game_engine.h"


// gl debuging funktion in der funktion kann alles gemacht werden
void openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cout << "[OpenGL Error] " << message << std::endl;
}

void getDirection(glm::vec3* direction, float yaw, float pitch) {
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	glm::normalize(front);
	direction->x = front.x;
	direction->y = front.y;
	direction->z = front.z;
}

/*
void resizeWindow(int windowWidth, int windowHeight, Camera* camera, gui::TextRenderer* textRend) {
	std::cout << "MESSAGE: Window width, height ... " << std::endl << "Width: " << windowWidth << " Height: " << windowHeight << std::endl;
	glViewport(0, 0, windowWidth, windowHeight);
	camera->updateRatio(windowWidth, windowHeight);
	textRend->rezise(windowWidth, windowHeight);
}
*/

namespace gameengine {
	GameEngine::GameEngine() {

	}

	GameEngine::GameEngine(int screenWidth, int screenHeight, Shader* fontShader) {
		textRend = gui::TextRenderer(screenWidth, screenHeight, fontShader);
		textRend.loadFont("fonts/arial.ttf");
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
	}

	void GameEngine::getDirection(glm::vec3* direction, float yaw, float pitch) {
		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		glm::normalize(front);
		direction->x = front.x;
		direction->y = front.y;
		direction->z = front.z;
	}

	
	void GameEngine::renderText(std::string text, float x, float y, float scale, glm::vec3 color) {
		textRend.renderText(text, x, y, scale, color);
	}
	

	void GameEngine::resizeWindow(int width, int height) {
		textRend.rezise(width, height);
		_screenHeight = height;
		_screenWidth = width;
	}

	int GameEngine::getScreenWidth() {
		return _screenWidth;
	}

	int GameEngine::getScreenHeight() {
		return _screenHeight;
	}
}