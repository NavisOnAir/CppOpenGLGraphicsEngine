#include "directional_light.h"

DirectionalLight::DirectionalLight() {

}

DirectionalLight::DirectionalLight(Shader* _s, float _yaw, float _pitch, glm::vec3 _color) {
	yaw = _yaw;
	pitch = _pitch;
	shader = _s;
	color = _color;
	shader->bind();

	directionLocation = glGetUniformLocation(shader->getShaderId(), "u_directional_light.direction");
	colorLocation = glGetUniformLocation(shader->getShaderId(), "u_directional_light.color");
	getDirection(&direction, yaw, pitch);
	glUniform3fv(colorLocation, 1, (float*)&color);

	// matrices locations
	modelViewProjLocation = glGetUniformLocation(shader->getShaderId(), "u_modelViewProj");
	modelViewLocation = glGetUniformLocation(shader->getShaderId(), "u_modelView");
	invModelViewLocation = glGetUniformLocation(shader->getShaderId(), "u_invModelView");
}

void DirectionalLight::getDirection(glm::vec3* _direction, float _yaw, float _pitch) {
	glm::vec3 front;
	front.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
	front.y = sin(glm::radians(_pitch));
	front.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
	glm::normalize(front);
	_direction->x = front.x;
	_direction->y = front.y;
	_direction->z = front.z;
}

void DirectionalLight::update(glm::mat4 cameraView) {
	shader->bind();
	glm::vec4 transformedDirection = glm::transpose(glm::inverse(cameraView))* glm::vec4(direction, 1.0f);
	glUniform3fv(directionLocation, 1, (float*)&transformedDirection);
}