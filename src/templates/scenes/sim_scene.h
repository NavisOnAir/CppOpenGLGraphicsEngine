#pragma once
#include "../../game_engine/scene/scene.h"
#include "../ui/default_ui.h"
#include "../../game_engine/model/Shapes/plane.h"

class SimScene : public Scene {
	SimScene(gameengine::GameEngine* pGameEngine);
	void render() override;
	int event() override;
};
