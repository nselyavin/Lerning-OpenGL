#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera
{
	glm::vec3 cameraPos;
	glm::vec3 cameraDirect;
	glm::vec3 cameraFront;
	
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
public:
	Camera() {
		cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
		setFront(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	Camera(float x, float y, float z) {
		cameraPos = glm::vec3(x, y, z);
		setFront(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	Camera(glm::vec3 cameraPos) {
		this->cameraPos = cameraPos;
		setFront(glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void setPos(float x, float y, float z) {
		cameraPos = glm::vec3(x, y, z);
	}

	void setPos(glm::vec3 cameraPos) {
		this->cameraPos = cameraPos;
	}

	void setFront(float x, float y, float z) {
		// Получаем вектор направления
		cameraFront = glm::vec3(x, y, z);
	}

	void setFront(glm::vec3 cameraFront) {
		// Получаем вектор направления
		this->cameraFront = cameraFront;
	}
	
	glm::vec3& getPos() {
		return cameraPos;
	}

	glm::vec3& getDirect() {
		return cameraDirect;
	}

	glm::mat4 getView() {
		cameraDirect = glm::normalize(cameraPos + cameraFront);
		return glm::lookAt(cameraPos, cameraDirect, cameraUp);
	}

};

