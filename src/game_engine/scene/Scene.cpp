#include "scene.h"

// private
void Scene::resizeWindow(int width, int height) {
	std::cout << "MESSAGE: Window width, height ... " << std::endl << "Width: " << width << " Height: " << height << std::endl;
	glViewport(0, 0, width, height);
	camera.updateRatio(width, height);
	mpUserInterface->resizeWindow(width, height);
	gameEngine->resizeWindow(width, height);
}

// public
Scene::Scene(gameengine::GameEngine* gameEngineptr) {
	std::cout << "init scene" << std::endl;
	gameEngine = gameEngineptr;

	// ui
	uiShader.init("src/shaders/ui.vert", "src/shaders/ui.frag");
	uiShader.bind();
	mpUserInterface = new gui::Ui(800, 600, &uiShader, gameEngine);

	// model shader
	modelShader = new Shader();
	modelShader->init("src/shaders/basic.vert", "src/shaders/basic.frag");
	modelShader->bind();

	// camera
	camera = OverviewCamera(90.0f, 800.0f, 600.0f);
	camera.translate(glm::vec3(0.0f, 10.0f, 0.0f));
	camera.setViewAngle(45.0f, -35.0f);
	camera.update();

	// lighting
	sunLight = DirectionalLight(modelShader, 45.0f, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	// matrices
	modelViewProjMatrixLocation = glGetUniformLocation(modelShader->getShaderId(), "u_modelViewProj");
	modelViewLocation = glGetUniformLocation(modelShader->getShaderId(), "u_modelView");
	invModelViewLocation = glGetUniformLocation(modelShader->getShaderId(), "u_invModelView");
	
}

Scene::~Scene() {
	delete mpUserInterface;
}

void Scene::setCamera(OverviewCamera* cam) {
	camera = *cam;
}

Camera Scene::getCamera() {
	return camera;
}

void Scene::addModel(model::Model* m) {
	models.push_back(m);
}

void Scene::addModels(model::Model** m, int count) {
	for (int i = 0; i < count; i++) {
		models.push_back(m[i]);
	}
}

void Scene::addSunLight(DirectionalLight dirLight) {
	sunLight = dirLight;
}

void Scene::setUi(gui::Ui ui) {
	mpUserInterface = &ui;
}

void Scene::setUi(gui::Ui* uiptr) {
	mpUserInterface = uiptr;
}

Shader* Scene::getShader() {
	return modelShader;
}

void Scene::render() {
	mpUserInterface->render();

	// lighting
	sunLight.update(camera.getView());

	// model rendering
	for (model::Model* m : models) {
		m->render(camera.getView(), camera.getViewProj(), modelViewProjMatrixLocation, modelViewLocation, invModelViewLocation);
	}
}

int Scene::event() {
	// key pressed
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return 1;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				keyW = true;
				break;
			case SDLK_a:
				keyA = true;
				break;
			case SDLK_s:
				keyS = true;
				break;
			case SDLK_d:
				keyD = true;
				break;
			case SDLK_LSHIFT:
				keyLShift = true;
				break;
			case SDLK_SPACE:
				keySpace = true;
				break;
			default:
				std::cout << event.key.keysym.sym << std::endl;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				keyW = false;
				break;
			case SDLK_a:
				keyA = false;
				break;
			case SDLK_s:
				keyS = false;
				break;
			case SDLK_d:
				keyD = false;
				break;
			case SDLK_LSHIFT:
				keyLShift = false;
				break;
			case SDLK_SPACE:
				keySpace = false;
				break;
			}
		}
		else if (event.type == SDL_MOUSEMOTION) {
			mpUserInterface->testCollision(event.motion.x, event.motion.y);
			if (SDL_GetRelativeMouseMode())
				camera.changeViewAngle(event.motion.xrel, event.motion.yrel);
			if (mouseRight) {
				camera.movePlane(event.motion.xrel, event.motion.yrel);
			}
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			switch (event.button.button) {
			case SDL_BUTTON_MIDDLE:
				SDL_SetRelativeMouseMode(SDL_TRUE);
				break;
			case SDL_BUTTON_RIGHT:
				mpUserInterface->rightMouseDown(event.button.x, event.button.y);
				mouseRight = true;
				break;
			case SDL_BUTTON_LEFT:
				mpUserInterface->leftMouseDown(event.button.x, event.button.y);
				break;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP) {
			switch (event.button.button) {
			case SDL_BUTTON_MIDDLE:
				SDL_SetRelativeMouseMode(SDL_FALSE);
				break;
			case SDL_BUTTON_RIGHT:
				mouseRight = false;
				mpUserInterface->rightMouseUp();
				break;
			case SDL_BUTTON_LEFT:
				mpUserInterface->leftMouseUp();
				break;
			}
		}
		else if (event.type == SDL_WINDOWEVENT) {
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				std::cout << "MESSAGE:Resizing window..." << std::endl;
				resizeWindow(event.window.data1, event.window.data2);
			}
		}
		else if (event.type == SDL_MOUSEWHEEL) {
			camera.zoom(event.wheel.preciseY);
		}
	}
	return 0;
}