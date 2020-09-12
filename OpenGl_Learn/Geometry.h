#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"

class Geometry
{
protected:
	GLuint VBO, VAO, EBO;
	float* verticles;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

public:
	Geometry() {
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		scale = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	Geometry(float posx, float posy, float posz) {
		position = glm::vec3(posx, posy, posz);
		rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		scale = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	virtual void draw() = 0;


};

