#pragma once
#include "gui/text/text_renderer.h"

#include <vector>

#include "../../libs/glm/glm.hpp"

#include <iostream>
#include <thread>

void openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

namespace gameengine {
	class GameEngine {
	public:
		GameEngine();
		GameEngine(int screenWidth, int screenHeight, Shader* fontShader);
		void getDirection(glm::vec3* direction, float yaw, float pitch);
		void renderText(std::string text, float x, float y, float scale, glm::vec3 color);
		void resizeWindow(int width, int height);
		int getScreenWidth();
		int getScreenHeight();
		gui::TextRenderer textRend;
	private:
		int _screenWidth;
		int _screenHeight;
	};
}