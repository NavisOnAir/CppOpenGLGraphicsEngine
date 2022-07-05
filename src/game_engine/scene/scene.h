#pragma once
#include "../defines.h"
#include "../game_engine.h"
#include "../gui/ui.h"
#include "../model/model.h"
#include "../model/shader.h"
#include "../camera/overview_camrera.h"
#include "../gui/widget/mesh2d.h"
#include "directional_light.h"
#include "../gui/shapes/rectangle.h"

#include <vector>

class Scene {
public:
	Scene(gameengine::GameEngine* gameEngineptr);
	~Scene();
	virtual void render();
	virtual int event();

	// engine
	gameengine::GameEngine* gameEngine;

	// model
	void addModel(model::Model* m);
	void addModels(model::Model** m, int count);

	// shader
	Shader* getShader();

	// lighting
	void addSunLight(DirectionalLight dirLight);

	// camera
	void setCamera(OverviewCamera* cam);
	Camera getCamera();

	// ui
	void setUi(gui::Ui ui);
	void setUi(gui::Ui* uiptr);

protected:
	// interface / window
	gui::Ui* mpUserInterface;
	Shader uiShader;
	void resizeWindow(int width, int height);

	// model
	std::vector<model::Model*> models;
	Shader* modelShader;
	int modelViewProjMatrixLocation;
	int modelViewLocation;
	int invModelViewLocation;

	// camera
	OverviewCamera camera;
	

	// lighting
	DirectionalLight sunLight;

	// keys
	bool keyW = false;
	bool keyA = false;
	bool keyS = false;
	bool keyD = false;
	bool keyLShift = false;
	bool keySpace = false;
	bool mouseRight = false;

};