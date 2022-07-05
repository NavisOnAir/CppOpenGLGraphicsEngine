#pragma once
#include "../../game_engine/gui/ui.h"

class MainUi : public gui::Ui {
public:
	MainUi();
	MainUi(int width, int height, Shader* uiShader, gameengine::GameEngine* pGameEngine);
	~MainUi();

	// visual
	void render() override;

	// event
	void leftMouseDown(int x, int y) override;
private:

};