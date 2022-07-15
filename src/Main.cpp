#include "game_engine/game_engine.h"
#include "game_engine/model/model.h"
#include "game_engine/camera/overview_camrera.h"
#include "game_engine/scene/scene.h"
#include "templates/scenes/title_scene.h"


// scenes
std::vector<Scene*> scenes;
Scene* activeScene;

int main(int argc, char** argv) {
	gameengine::GameEngine gameEngine;
	SDL_Window* window;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(-1); // 0 = kein vsync; 1 = vsync; -1 = adaptive sync

#ifdef _DEBUG
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

	uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

	window = SDL_CreateWindow("C++ OpenGL Tutorial", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		std::cin.get();
		return -1;
	}
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openGLDebugCallback, 0);
#endif

	// font things
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Shader fontShader;
	fontShader.init("src/shaders/font.vert", "src/shaders/font.frag");
	//gui::TextRenderer textRend(800, 600, &fontShader);
	//textRend.loadFont("fonts/arial.ttf");
	gameEngine = gameengine::GameEngine(800, 600, &fontShader);

	Shader shader;
	shader.init("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.bind();


	model::Model tree;
	tree.init("models/tree.bmf", &shader, 0.01f, glm::vec3(0.0f, 80.0f, 0.0f));
	model::Model normalCude;
	normalCude.init("models/customTerrain.bmf", &shader, 1.0f, glm::vec3(-50.0f, 0.0f, -50.0f));

	uint64 perfCounterFrequency = SDL_GetPerformanceFrequency();
	uint64 lastCounter = SDL_GetPerformanceCounter();
	float32 delta = 0.0f;

	DirectionalLight dirL(&shader, 45.0f, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f) * 0.95f);

	// scene
	
	model::Model* modelsArr[2];
	modelsArr[0] = &normalCude;
	modelsArr[1] = &tree;

	Scene defaultScene(&gameEngine);
	defaultScene.addModels(modelsArr, 2);
	defaultScene.addSunLight(dirL);

	// ui
	Shader uiShader;
	uiShader.init("src/shaders/ui.vert", "src/shaders/ui.frag");
	MainUi *userInt = new MainUi(gameEngine.getScreenWidth(), gameEngine.getScreenHeight(), &uiShader, &gameEngine);
	defaultScene.setUi(userInt);

	// TitleScene MainMenu(&gameEngine);

	//Scene simScene(&gameEngine);

	//activeScene = &simScene;

	// Wireframe
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	bool close = false;
	// game loop
	while (!close) {
		// event handeling
		if (defaultScene.event()) {
			close = true;
		}

		glClearColor(0.1529f, 0.5412f, 0.9098f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		defaultScene.render();
		//gameEngine.textRend.renderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

		uint64 endCounter = SDL_GetPerformanceCounter();
		uint64 counterElapsed = endCounter - lastCounter;
		delta = ((float32)counterElapsed) / (float32)perfCounterFrequency;
		uint32 FPS = (uint32)((float32)perfCounterFrequency / (float32)counterElapsed);
		lastCounter = endCounter;
		gameEngine.textRend.renderText(std::to_string(FPS), 0, gameEngine.getScreenHeight() * 0.9f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

		SDL_GL_SwapWindow(window);
	}
	return 0;
}