#pragma once
#include "camera.h"
#include "../../../libs/glm/gtc/matrix_transform.hpp"

class FlyCamera : public Camera {
public:
	FlyCamera(float fov, float width, float height) : Camera(fov, width, height) {
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		yaw = -90.0f;
		pitch = 0.0f;
		onMouseMoved(0.0f, 0.0f);
		update();
	};
	void onMouseMoved(float xRel, float yRel);
	void update() override;
	void moveFront(float amount);
	void moveSideways(float amount);
	void moveUp(float amount);

private:
	float yaw;
	float pitch;
	glm::vec3 lookAt;
	const float mouseSensitivity = 0.1f;
	glm::vec3 up;
};