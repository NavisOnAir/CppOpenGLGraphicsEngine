#include "default_ui.h"

MainUi::MainUi() {

}

MainUi::MainUi(int width, int height, Shader* uiShader, gameengine::GameEngine* pGameEngine) : Ui(width, height, uiShader, pGameEngine) {
	gui::Button* mpButton1 = new gui::Button(0, 0, 100, 100, mscreenWidth, mscreenHeight, mpShader, &mProjectionMatrix, mpGameEngine);
	mButtons.push_back(mpButton1);
	mpButton1->setColor({ 1.0f, 0.0f, 0.0f, 1.0f });

	gui::Button* mpButton2 = new gui::Button(110, 0, 100, 100, mscreenWidth, mscreenHeight, mpShader, &mProjectionMatrix, mpGameEngine);
	mButtons.push_back(mpButton2);
	mpButton2->setColor({ 0.0f, 1.0f, 0.0f, 1.0f });

	gui::Button* mpButton3 = new gui::Button(220, 0, 100, 100, mscreenWidth, mscreenHeight, mpShader, &mProjectionMatrix, mpGameEngine);
	mButtons.push_back(mpButton3);
	mpButton3->setColor({ 0.0f, 0.0f, 1.0f, 1.0f });

}

MainUi::~MainUi() {
	delete[] mButtons.data();
	delete[] mRects.data();
}

// visual
void MainUi::render() {
	for (gui::Button* pButton : mButtons) {
		pButton->render();
	}
}

// event
void MainUi::leftMouseDown(int x, int y) {
	int testY = y + mscreenHeight - 2 * y;
	for (gui::Button* pButton : mButtons) {
		if (pButton->testCollision(x, testY)) {
			pButton->onLeftClickDown();
		}
	}
}
