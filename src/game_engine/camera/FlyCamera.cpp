#include "flyCamera.h"

void FlyCamera::onMouseMoved(float xRel, float yRel) {
	yaw += xRel * mouseSensitivity;
	pitch -= yRel * mouseSensitivity;
	// clamp maximale Neigung
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	lookAt = glm::normalize(front);
	update();
}

void FlyCamera::update() {
	view = glm::lookAt(position, position + lookAt, up);
	viewProj = projection * view;
}

void FlyCamera::moveFront(float amount) {
	translate(glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f) * lookAt) * amount);
	update();
}

void FlyCamera::moveSideways(float amount) {
	translate(glm::normalize(glm::cross(lookAt, up)) * amount);
	update();
}

void FlyCamera::moveUp(float amount) {
	translate(up * amount);
}