#include "overview_camrera.h"

/*
OverviewCamera::OverviewCamera() {
	yaw = 0.0f;
	pitch = 0.0f;
	lookAt = glm::vec3(1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}
*/
OverviewCamera::OverviewCamera() {

}

OverviewCamera::OverviewCamera(float fov, float width, float height) : Camera(fov, width, height) {
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	changeViewAngle(0.0f, 0.0f);
	update();
};

void OverviewCamera::update() {
	view = glm::lookAt(position, position + lookAt, up);
	viewProj = projection * view;
}

void OverviewCamera::changeViewAngle(float xRel, float yRel) {
	yaw += xRel * mouseLookSensitivity;
	pitch -= yRel * mouseLookSensitivity;
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

void OverviewCamera::setViewAngle(float i_yaw, float i_pitch) {
	yaw = i_yaw;
	pitch = i_pitch;

	glm::vec3 direction;
	direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	direction.y = sin(glm::radians(pitch));
	direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	lookAt = glm::normalize(direction);
	update();
}

void OverviewCamera::movePlane(float xRel, float yRel) {
	glm::vec3 xMove = cross(lookAt * glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, -xRel, 0.0f));
	glm::vec3 zMove = cross(glm::vec3(-lookAt.z, 0.0f, lookAt.x), glm::vec3(0.0f, -yRel, 0.0f));
	glm::vec3 moveVector = xMove + zMove;
	translate(moveVector * mouseMoveSensitivity * position.y);
	update();
}

void OverviewCamera::zoom(float amount) {
	if (position.y > 0) {
		translate(lookAt * amount * mouseZoomSensitivity);
		// clamp maximum zoom
		if (position.y < 1.0f) {
			position.y = 1.0f;
		}
		update();
	}
	else {
		position.y = 0.2f;
	}
}