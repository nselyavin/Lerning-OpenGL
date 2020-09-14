#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

#include "Material.h"

class Geometry
{
protected:
	GLuint VBO, VAO;
	float* verticles;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 transform;
	Material* material;

public:
	Geometry() {
		VBO = 0;
		VAO = 0;
		verticles = nullptr;
		material = nullptr;
		position = glm::vec3(1.0f);
		rotation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
	}

	Geometry(float posx, float posy, float posz) {
		VBO = 0;
		VAO = 0;
		verticles = nullptr;
		material = nullptr;
		position = glm::vec3(posx, posy, posz);
		rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		scale = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	virtual void draw() = 0;

	void setMaterial(Material* material) {
		this->material = material;
	}

	~Geometry() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

protected:
	void acceptTransform() {
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		// ToDo преобразовать вектор3 в кватернион \\
		transform = glm::rotate(transform, )
	}
};

