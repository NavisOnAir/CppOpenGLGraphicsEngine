#pragma once
#include "camera.h"
#include "../../../libs/glm/gtc/matrix_transform.hpp"

class OverviewCamera : public Camera {
public:
	OverviewCamera();
	OverviewCamera(float fov, float width, float height);
	void zoom(float amount);
	void changeViewAngle(float xRel, float yRel);
	void update() override;
	void movePlane(float xRel, float yRel);
	void setViewAngle(float i_yaw, float i_pitch);
private:
	float yaw;
	float pitch;
	glm::vec3 lookAt;
	float mouseSensitivity = 0.1f;
	float mouseLookSensitivity = 1.0f * mouseSensitivity;
	float mouseMoveSensitivity = 0.1f * mouseSensitivity;
	float mouseZoomSensitivity = 10.0f * mouseSensitivity;
	glm::vec3 up;
};