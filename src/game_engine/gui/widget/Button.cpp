#include "button.h"

namespace gui {
	Button::Button() {
		mx = 0;
		my = 0;
		mwidth = 0;
		mheight = 0;
		mscreenWidth = 0;
		mscreenHeight = 0;
		misHovered = false;

		// events
		misLeftClicked = false;
		misRightClicked = false;
	}

	Button::Button(int posX, int posY, float buttonWidth, float buttonHeight, int screenWidth, int screenHeight, Shader* uiShader, glm::mat4* projMatptr, gameengine::GameEngine* pGameEngine) {
		mx = posX;
		my = posY;
		mtextX = posX;
		mtextY = posY;
		mwidth = buttonWidth;
		mheight = buttonHeight;
		mscreenWidth = screenWidth;
		mscreenHeight = screenHeight;
		misHovered = false;
		misLeftClicked = false;
		misRightClicked = false;
		mpGameEngine = pGameEngine;
		mtext = "";

		mModel = gui::Rectangle(posX, posY, buttonWidth, buttonHeight, screenWidth, screenHeight, uiShader, projMatptr);
	}

	void Button::senseHover(bool isCollided) {
		if (isCollided) {
			onHover();
			if (!misHovered) {
				misHovered = true;
				onHoverEnter();
			}
		}
		else {
			if (misHovered) {
				misHovered = false;
				onHoverExit();
			}
		}
		
	}

	// events
	void Button::onHoverEnter() {
		mModel.changeColor(gui::Color{ 1.0f, 0.0f, 0.0f, 1.0f });
		mModel.updatePosition(0, 5);
		onHover();
	}

	void Button::onHover() {
		mModel.changeColor(gui::Color{ 0.0f, 0.0f, 1.0f, 0.5f });
		if (misLeftClicked) {
			onLeftClick();
		}
		if (misRightClicked) {
			onRightClick();
		}
	}

	void Button::onHoverExit() {
		mModel.changeColor(gui::Color{ 1.0f, 1.0f, 1.0f, 1.0f });
		mModel.updatePosition(0, -5);
	}

	void Button::onLeftClickDown() {
		misLeftClicked = true;
		onLeftClick();
	}

	void Button::onLeftClick() {
		mModel.changeColor(gui::Color{ 1.0f, 0.0f, 1.0f, 1.0f });
	}

	void Button::onLeftClickUp() {
		misLeftClicked = false;
		mModel.changeColor(gui::Color{ 1.0f, 1.0f, 1.0f, 1.0f });
	}

	void Button::onRightClickDown() {
		misRightClicked = true;
		onRightClick();
	}

	void Button::onRightClick() {
		mModel.changeColor(gui::Color{ 0.0f, 1.0f, 1.0f, 0.5f });
	}

	void Button::onRightClickUp() {
		misRightClicked = false;
		mModel.changeColor(gui::Color{ 1.0f, 1.0f, 1.0f, 1.0f });
	}

	// detection

	int Button::testCollision(int testX, int testY) {
		if (mx < testX && mx + mwidth > testX) {
			if (my < testY && my + mheight > testY) {
				senseHover(true);
				return 1;
			}
		}
		senseHover(false);
		return 0;
	}

	// visual
	void Button::render() {
		mModel.render();
		if (!std::empty(mtext)) {
			mpGameEngine->renderText(mtext, mtextX, mtextY, 1.0f, glm::vec3(0.0f));
		}
	}

	void Button::resizeWindow(int width, int height) {
		mscreenWidth = width;
		mscreenHeight = height;
	}

	// set
	void Button::setTextCoords(int x, int y) {
		mtextX = x;
		mtextY = y;
	}

	void Button::setColor(gui::Color Color) {
		mModel.changeColor(Color);
	}

	void Button::setText(std::string text) {
		mtext = text;
	}

	// get methods
	int Button::getX() {
		return mx;
	}

	int Button::getY() {
		return my;
	}

	int Button::getYTransformed() {
		return my + mscreenHeight - 2 * my;
	}

	float Button::getWidth() {
		return mwidth;
	}

	float Button::getHeight() {
		return mheight;
	}

	int Button::getCenteredX() {
		return mx + mwidth / 2;
	}

	int Button::getCenteredY() {
		return my + mheight / 2;
	}

	std::string Button::getText() {
		return mtext;
	}
}