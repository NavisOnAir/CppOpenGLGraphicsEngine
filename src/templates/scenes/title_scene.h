#pragma once
#include "../ui/default_ui.h"
#include "../../game_engine/scene/scene.h"
#include "../../game_engine/model/Shapes/plane.h"

#include <string>

class TitleScene : public Scene {
public:
	TitleScene(gameengine::GameEngine* pGameEngine);
	void render() override;
	int event() override;
};