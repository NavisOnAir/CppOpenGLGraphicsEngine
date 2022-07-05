#pragma once
#include "../shapes/rectangle.h"
#include "../../game_engine.h"

#include <string>

namespace gui {
	class Button {
	public:
		Button();
		Button(int posX, int posY, float buttonWidth, float buttonHeight, int screenWidth, int screenHeight, Shader* uiShader, glm::mat4* projMatptr, gameengine::GameEngine* pGameEngine);
		void senseHover(bool isCollided);
		virtual void onHoverEnter();
		virtual void onHover();
		virtual void onHoverExit();
		virtual void onLeftClickDown();
		virtual void onLeftClick();
		virtual void onLeftClickUp();
		virtual void onRightClickDown();
		virtual void onRightClick();
		virtual void onRightClickUp();

		// manipulation
		

		int testCollision(int x, int y);
		void render();
		void resizeWindow(int width, int height);

		// set methods
		void setTextCoords(int x, int y);
		void setText(std::string text);
		void setColor(gui::Color Color);

		// get methods
		int getX();
		int getY();
		int getYTransformed();
		float getWidth();
		float getHeight();
		int getCenteredX();
		int getCenteredY();
		std::string getText();
	private:
		// general
		gameengine::GameEngine* mpGameEngine;
		 
		// properties
		int mx, my, mscreenWidth, mscreenHeight;
		float mwidth, mheight;
		std::string mtext;

		// visuals
		gui::Rectangle mModel;
		int mtextX, mtextY;

		// interaction
		bool misHovered;
		bool misLeftClicked;
		bool misRightClicked;
	};
}
