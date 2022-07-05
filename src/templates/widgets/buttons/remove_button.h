#pragma once
#include "../../../game_engine/gui/widget/button.h"

class RemoveButton : public gui::Button {
public:
	RemoveButton();
	RemoveButton(int posX, int posY, float buttonWidth, float buttonHeight, int screenWidth, int screenHeight, Shader* pUiShader, glm::mat4* pProjMat, gameengine::GameEngine* pGameEngine);
	void onLeftClickDown() override;
};