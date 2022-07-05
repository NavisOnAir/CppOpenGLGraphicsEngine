#pragma once
#include "text/text_renderer.h"
#include "shapes/rectangle.h"
#include "widget/mesh2d.h"
#include "widget/form.h"
#include "widget/button.h"
#include "../game_engine.h"

#include <vector>

namespace gui {
	class Ui {
	public:
		Ui();
		Ui(int width, int height, Shader* uiShader, gameengine::GameEngine* pGameEngine);

		// rendering
		virtual void render();
		Shader* getShader();
		glm::mat4* getProj();

		// updating
		void resizeWindow(int width, int height);
		virtual int testCollision(int x, int y);

		// mousebuttons
		virtual void leftMouseDown(int x, int y);
		virtual void leftMouseUp();
		virtual void rightMouseDown(int x, int y);
		virtual void rightMouseUp();

	protected:
		int mscreenWidth, mscreenHeight;

		// rendering
		Shader* mpShader;
		gameengine::GameEngine* mpGameEngine;
		glm::mat4 mProjectionMatrix;

		// mesh
		std::vector<gui::Rectangle*> mRects;

		// ui elements
		std::vector<gui::Button*> mButtons;
	};
}