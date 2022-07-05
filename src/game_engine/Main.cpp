#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <map>

#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED

#include "../../libs/glm/glm.hpp"
#include "../../libs/glm/ext/matrix_transform.hpp"
#include "../../libs/glm/gtc/matrix_transform.hpp"
#include "../../libs/glm/gtc/type_ptr.hpp"

#ifdef _WIN32
#include <SDL.h>
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")
#else
#include <SDL2/SDL.h>
#endif

//#include "defines.h"
#include "model/vertexBuffer.h"
#include "model/shader.h"
#include "model/indexBuffer.h"
#include "model/model.h"
#include "camera/overview_camrera.h"
#include "gui/text/text_renderer.h"
#include "game_engine.h"

#include <ft2build.h>
#include FT_FREETYPE_H

std::map<char, Character> characters;
uint32 FONT_VAO, FONT_VBO;

/*
void getDirection(glm::vec3* direction, float yaw, float pitch) {
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	glm::normalize(front);
	direction->x = front.x;
	direction->y = front.y;
	direction->z = front.z;
}
*/

int mainT(int argc, char** argv) {
	SDL_Window* window;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1); // 0 = kein vsync; 1 = vsync; -1 = adaptive sync

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

	// Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader shader;
	shader.init("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.bind();
	
	float sunYaw = 45.0f;
	float sunPitch = 0.0f;
	int directionLocation = glGetUniformLocation(shader.getShaderId(), "u_directional_light.direction");
	int colorLocation = glGetUniformLocation(shader.getShaderId(), "u_directional_light.color");
	glm::vec3 sunColor = glm::vec3(1.0f) * 0.95f;
	glm::vec3 sunDirection;
	getDirection(&sunDirection, sunYaw, sunPitch);
	glUniform3fv(colorLocation, 1, (float*)&sunColor);
	

	// point light
	//Model pointLight;
	//pointLight.init("models/sphere.bmf", &shader, 0.01f);
	//pointLight.move(glm::vec3(0.0f, 0.0f, 10.0f));
	/*
	glm::vec3 pointLightColor = glm::vec3(0.0f, 0.0f, 0.0f);
	int pointLightPositionLocation = glGetUniformLocation(shader.getShaderId(), "u_point_light.position");
	int pointLightDiffuseLocation = glGetUniformLocation(shader.getShaderId(), "u_point_light.diffuse");
	int pointLightSpecularLocation = glGetUniformLocation(shader.getShaderId(), "u_point_light.specular");
	int pointLightAmbientLocation = glGetUniformLocation(shader.getShaderId(), "u_point_light.ambient");
	glUniform3fv(pointLightDiffuseLocation, 1, (float*)&pointLightColor);
	glUniform3fv(pointLightSpecularLocation, 1, (float*)&pointLightColor);
	pointLightColor *= 0.1f;
	glUniform3fv(pointLightAmbientLocation, 1, (float*)&pointLightColor);
	glm::vec4 pointLightPosition = glm::vec4(0.0f, 0.0f, 10.0f, 1.0f);
	glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_point_light.linear"), 0.027f);
	glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_point_light.quadratic"), 0.0028f);*/

	/*
	glm::vec3 pointLightColor = glm::vec3(0.0f, 0.0f, 1.0f);
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_point_light.diffuse"), 1, (float*)&pointLightColor);
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_point_light.specular"), 1, (float*)&pointLightColor);
	pointLightColor *= 0.2f;
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_point_light.ambient"), 1, (float*)&pointLightColor);
	glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_point_light.linear"), 0.027f);
	glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_point_light.quadratic"), 0.0028f);
	glm::vec4 pointLightPosition = glm::vec4(0.0f, 0.0f, 10.0f, 1.0f);
	int positionLocation = glGetUniformLocation(shader.getShaderId(), "u_point_light.position");
	*/
	
	/*
	// spot light
	glm::vec3 spotLightColor = glm::vec3(1.0f);
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.diffuse"), 1, (float*)&spotLightColor);
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.specular"), 1, (float*)&spotLightColor);
	spotLightColor *= 0.001f;
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.ambient"), 1, (float*)&spotLightColor);
	glm::vec3 spotLightPosition = glm::vec3(0.0f);
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.position"), 1, (float*)&spotLightPosition);
	glm::vec3 spotLightDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	glUniform3fv(glGetUniformLocation(shader.getShaderId(), "u_spot_light.direction"), 1, (float*)&spotLightDirection);
	glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_spot_light.innerCone"), 0.99f);
	glUniform1f(glGetUniformLocation(shader.getShaderId(), "u_spot_light.outerCone"), 0.90f);
	*/

	std::vector<model::Model*> treeModels;
	model::Model tree;
	tree.init("models/tree.bmf", &shader, 0.01f, glm::vec3(0.0f, 80.0f, 0.0f));
	model::Model plane;
	plane.init("models/fbxCube.bmf", &shader, 0.01f, glm::vec3(0.0f));
	model::Model normalCude;
	normalCude.init("models/customTerrain.bmf", &shader, 1.0f, glm::vec3(-50.0f, 0.0f, -50.0f));
	// normalCude.init("models/tile.bmf", &shader, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
	for (int i = 0; i < 10; i++) {
		float randX = ((float)(rand() % 2000)) - 1000.0f;
		float randZ = ((float)(rand() % 2000)) - 1000.0f;
		model::Model* treeModel = new model::Model;
		treeModel->init("models/tree.bmf", &shader, 0.01f, glm::vec3(randX, 80.0f, randZ));
		treeModels.push_back(treeModel);
	}

	uint64 perfCounterFrequency = SDL_GetPerformanceFrequency();
	uint64 lastCounter = SDL_GetPerformanceCounter();
	float32 delta = 0.0f;

	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::scale(model, glm::vec3(0.1f));

	//FlyCamera camera(90.0f, 800.0f, 600.0f);
	//camera.translate(glm::vec3(0.0f, 0.0f, 5.0f));
	//camera.update();
	OverviewCamera oCamera(90.0f, 800.0f, 600.0f);
	oCamera.translate(glm::vec3(0.0f, 10.0f, 0.0f));
	oCamera.setViewAngle(45.0f, -35.0f);
	oCamera.update();

	//glm::mat4 modelViewProj = camera.getViewProj() * model;

	int modelViewProjMatrixLocation = glGetUniformLocation(shader.getShaderId(), "u_modelViewProj");
	int modelViewLocation = glGetUniformLocation(shader.getShaderId(), "u_modelView");
	int invModelViewLocation = glGetUniformLocation(shader.getShaderId(), "u_invModelView");

	// Wireframe
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*
	// load fonts with freetyp
	glm::mat4 screenProjectionMatrix = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
	Shader fontShader("src/shaders/font.vert", "src/shaders/font.frag");
	fontShader.bind();
	GLuint fontProjectionMatrixLocation = glGetUniformLocation(fontShader.getShaderId(), "u_projection");
	glUniformMatrix4fv(fontProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(screenProjectionMatrix));


	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}

	FT_Face face;
	if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return -1;
	}
	else {

		FT_Set_Pixel_Sizes(face, 0, 48); // setting width to 0 lets the face dynamically size the letters based on demand

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

		for (unsigned char c = 0; c < 128; c++) {
			// load charayter glyph
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate textures
			uint32 texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// store characters
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// clear freetype's resources
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &FONT_VAO);
	glGenBuffers(1, &FONT_VBO);
	glBindVertexArray(FONT_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, FONT_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	*/
	gui::TextRenderer textRend(800, 600);
	textRend.loadFont("fonts/arial.ttf");
	

	



	// key pressed
	bool keyW = false;
	bool keyA = false;
	bool keyS = false;
	bool keyD = false;
	bool keyLShift = false;
	bool keySpace = false;
	bool mouseRight = false;

	float cameraSpeed = 5.0f;
	float time = 0.0f;
	bool close = false;
	float height = 0.6f;
	float speed = 0.01f;
	float c = 0.0f;
	float camSpeed = 5.0f;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	while (!close) {
		// event handeling
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				close = true;
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
				case SDLK_l:
					tree.move(glm::vec3(1.0f, 0.0f, 0.0f));
					plane.move(glm::vec3(1.0f, 0.0f, 0.0f));
					tree.printPos();
					break;
				case SDLK_i:
					tree.move(glm::vec3(0.0f, 1.0f, 0.0f));
					plane.move(glm::vec3(0.0f, 1.0f, 0.0f));
					tree.printPos();
					break;
				case SDLK_j:
					tree.move(glm::vec3(-1.0f, 0.0f, 0.0f));
					plane.move(glm::vec3(-1.0f, 0.0f, 0.0f));
					tree.printPos();
					break;
				case SDLK_k:
					tree.move(glm::vec3(0.0f, -1.0f, 0.0f));
					plane.move(glm::vec3(0.0f, -1.0f, 0.0f));
					tree.printPos();
					break;
				case SDLK_n:
					sunYaw++;
					getDirection(&sunDirection, sunYaw, sunPitch);
					break;
				case SDLK_m:
					sunYaw--;
					getDirection(&sunDirection, sunYaw, sunPitch);
					break;
				case SDLK_v:
					sunPitch++;
					getDirection(&sunDirection, sunYaw, sunPitch);
					break;
				case SDLK_b:
					sunPitch--;
					getDirection(&sunDirection, sunYaw, sunPitch);
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
				// std::cout << "x: " << event.motion.x << " y: " << event.motion.y << std::endl;
				if (SDL_GetRelativeMouseMode())
					//camera.onMouseMoved(event.motion.xrel, event.motion.yrel);
					oCamera.changeViewAngle(event.motion.xrel, event.motion.yrel);
				if (mouseRight) {
					oCamera.movePlane(event.motion.xrel, event.motion.yrel);
				}
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				switch (event.button.button) {
				case SDL_BUTTON_MIDDLE:
					SDL_SetRelativeMouseMode(SDL_TRUE);
					break;
				case SDL_BUTTON_RIGHT:
					mouseRight = true;
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
					break;
				}
			}
			else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
					std::cout << "MESSAGE:Resizing window..." << std::endl;
					resizeWindow(event.window.data1, event.window.data2, &oCamera, &textRend);
				}
			}
			else if (event.type == SDL_MOUSEWHEEL) {
				oCamera.zoom(event.wheel.preciseY);
			}
		}

		glClearColor(0.1529f, 0.5412f, 0.9098f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		time += delta;

		/*
		if (keyW) {
			camera.moveFront(delta * cameraSpeed);
		}
		if (keyA) {
			camera.moveSideways(-delta * cameraSpeed);
		}
		if (keyS) {
			camera.moveFront(-delta * cameraSpeed);
		}
		if (keyD) {
			camera.moveSideways(delta * cameraSpeed);
		}
		if (keyLShift) {
			camera.moveUp(-delta * cameraSpeed);
		}
		if (keySpace) {
			camera.moveUp(delta * cameraSpeed);
		}
		camera.update();*/
		
		/*
		model = glm::rotate(model, 0.6f * delta, glm::vec3(0, 1, 0));
		model = glm::translate(model, glm::vec3(0.0f, sinf(c) * height * delta, 0.0f));*/
		c += speed;
		
		
		/*
		modelViewProj = camera.getViewProj() * model;
		glm::mat4 modelView = camera.getView() * model;
		glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));
		*/
		shader.bind();
		glm::vec4 transformedSunDirection = glm::transpose(glm::inverse(oCamera.getView())) * glm::vec4(sunDirection, 1.0f);
		glUniform3fv(directionLocation, 1, (float*)&transformedSunDirection);

		// point light
		// glm::mat4 pointLightMatrix = glm::rotate(glm::mat4(1.0f), -delta, { 0.0f, 1.0f, 0.0f });
		//pointLight.rotate(delta)
		/*
		pointLightPosition = pointLightPosition * pointLightMatrix;
		glm::vec3 transformedPointLightPosition = (glm::vec3)(camera.getView() * pointLightPosition);
		glUniform3fv(positionLocation, 1, (float*)&transformedPointLightPosition);
		*/

		/*
		glUniformMatrix4fv(modelViewProjMatrixLocation, 1, GL_FALSE, &modelViewProj[0][0]);
		glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &modelView[0][0]);
		glUniformMatrix4fv(invModelViewLocation, 1, GL_FALSE, &invModelView[0][0]);
		*/
		
		//pointLight.render(camera.getView(), camera.getViewProj(), modelViewProjMatrixLocation, modelViewLocation, invModelViewLocation);
		tree.render(oCamera.getView(), oCamera.getViewProj(), modelViewProjMatrixLocation, modelViewLocation, invModelViewLocation);
		//plane.render(camera.getView(), camera.getViewProj(), modelViewProjMatrixLocation, modelViewLocation, invModelViewLocation);
		normalCude.render(oCamera.getView(), oCamera.getViewProj(), modelViewProjMatrixLocation, modelViewLocation, invModelViewLocation);
		for (model::Model* treeM : treeModels) {
			treeM->render(oCamera.getView(), oCamera.getViewProj(), modelViewProjMatrixLocation, modelViewLocation, invModelViewLocation);
		}
		//ground.render();

		// render fonts
		textRend.renderText("This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
		textRend.renderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

		

		SDL_GL_SwapWindow(window);

		

		uint64 endCounter = SDL_GetPerformanceCounter();
		uint64 counterElapsed = endCounter - lastCounter;
		delta = ((float32)counterElapsed) / (float32)perfCounterFrequency;
		uint32 FPS = (uint32)((float32)perfCounterFrequency / (float32)counterElapsed);
		lastCounter = endCounter;
	}

	return 0;
}