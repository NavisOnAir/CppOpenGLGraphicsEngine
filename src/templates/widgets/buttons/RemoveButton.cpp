#include "remove_button.h"

RemoveButton::RemoveButton() : Button() {

}

RemoveButton::RemoveButton(int posX, int posY, float buttonWidth, float buttonHeight, int screenWidth, int screenHeight, Shader* pUiShader, glm::mat4* pProjMat, gameengine::GameEngine* pGameEngine) : Button(posX, posY, buttonWidth, buttonHeight, screenWidth, screenHeight, pUiShader, pProjMat, pGameEngine) {

}

void RemoveButton::onLeftClickDown() {
	
}