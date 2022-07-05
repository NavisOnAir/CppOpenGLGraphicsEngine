#include "sim_scene.h"

SimScene::SimScene(gameengine::GameEngine* pGameEngine) : Scene(pGameEngine) {
	mpUserInterface = new MainUi(800, 600, &uiShader, pGameEngine);
	model::Plane plane(1.0f, 10, 10, modelShader, 1.0f, glm::vec3(0.0f));
	models.push_back(plane.getModelPtr());
}

void SimScene::render() {
	mpUserInterface->render();

	// lighting
	sunLight.update(camera.getView());

	// model rendering
	for (model::Model* m : models) {
		m->render(camera.getView(), camera.getViewProj(), modelViewProjMatrixLocation, modelViewLocation, invModelViewLocation);
	}
}

int SimScene::event() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return 1; // break gameloop
		}
		else if (event.type == SDL_MOUSEMOTION) {
			mpUserInterface->testCollision(event.motion.x, event.motion.y);
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
	}
	return 0;
}