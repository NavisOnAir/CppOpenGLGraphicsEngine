#pragma once
#include "../../../libs/glm/glm.hpp"
#include "../../../libs/glm/gtc/matrix_transform.hpp"

class Camera {
public:
	Camera();
	Camera(float fov, float width, float height);
	glm::mat4 getViewProj();
	glm::mat4 getView();
	virtual void update();
	virtual void updateRatio(float width, float height);
	virtual void translate(glm::vec3 v);

protected:
	glm::vec3 position;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 viewProj;
	float fov;
};