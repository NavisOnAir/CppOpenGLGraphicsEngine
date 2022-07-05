#include "ui.h"

namespace gui {

	Ui::Ui() {

	}

	Ui::Ui(int width, int height, Shader* uiShader, gameengine::GameEngine* pGameEngine) {
		mscreenWidth = width;
		mscreenHeight = height;
		mpShader = uiShader;
		mpGameEngine = pGameEngine;
		mProjectionMatrix = glm::ortho(0.0f, (float)mscreenWidth, 0.0f, (float)mscreenHeight);
	}

	
	void Ui::render() {

	}
	

	Shader* Ui::getShader() {
		return mpShader;
	}

	glm::mat4* Ui::getProj() {
		return &mProjectionMatrix;
	}

	void Ui::resizeWindow(int width, int height) {
		std::cout << "resizing ui" << std::endl;
		mscreenWidth = width;
		mscreenHeight = height;

		for (gui::Button* pButton : mButtons) {
			pButton->resizeWindow(mscreenWidth, mscreenHeight);
		}

		mpShader->bind();
		mProjectionMatrix = glm::ortho(0.0f, (float)mscreenWidth, 0.0f, (float)mscreenHeight);
		glUniformMatrix4fv(glGetUniformLocation(mpShader->getShaderId(), "u_projection"), 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
	}


	// hover over detection
	int Ui::testCollision(int x, int y) {
		int testY = y + mscreenHeight - 2 * y;
		for (gui::Button* pButton : mButtons) {
			if (pButton->testCollision(x, testY)) {
				return 1;
			}
		}
		return 0;
	}

	// clicked detection
	void Ui::leftMouseDown(int x, int y) {
		int testY = y + mscreenHeight - 2 * y;
		for (gui::Button* pButton : mButtons) {
			if (pButton->testCollision(x, testY)) {
				pButton->onLeftClickDown();
			}
		}
	}

	void Ui::leftMouseUp() {
		for (gui::Button* pButton : mButtons) {
			pButton->onLeftClickUp();
		}
	}

	void Ui::rightMouseDown(int x, int y) {
		int testY = y + mscreenHeight - 2 * y;
		for (gui::Button* pButton : mButtons) {
			if (pButton->testCollision(x, testY)) {
				pButton->onRightClickDown();
			}
		}
	}

	void Ui::rightMouseUp() {
		for (gui::Button* pButton : mButtons) {
			pButton->onRightClickUp();
		}
	}

}