#pragma once
#include "../model/shader.h"
#include "../defines.h"

class DirectionalLight {
private:
	Shader* shader;
	int modelViewProjLocation;
	int modelViewLocation;
	int invModelViewLocation;
	float yaw;
	float pitch;
	int directionLocation;
	int colorLocation;
	glm::vec3 color;
	glm::vec3 direction;

	void getDirection(glm::vec3* _direction, float _yaw, float _pitch);
public:
	DirectionalLight();
	DirectionalLight(Shader* _s, float _yaw, float _pitch, glm::vec3 _color);
	void update(glm::mat4 cameraView);

};