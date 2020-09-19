#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"

#include "Material.h"

class Geometry
{
protected:
	GLuint VBO, VAO;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	Material* material;
	float delta = 0;

public:
	Geometry() {
		VBO = 0;
		VAO = 0;
		material = nullptr;
		position = glm::vec3(0.0f);
		rotation = glm::vec3(0.0f);
		scale = glm::vec3(1.0f);
	}

	Geometry(float posx, float posy, float posz) {
		VBO = 0;
		VAO = 0;
		material = nullptr;
		position = glm::vec3(posx, posy, posz);
		rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		scale = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	virtual void draw(GLFWwindow* window) = 0;

	void setMaterial(Material* material) {
		this->material = material;
	}

	~Geometry() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

protected:
	void acceptTransform(GLFWwindow *window) {

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
		material->getShader()->setMat4("view", view);
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		model = glm::rotate(model, glm::radians((float)glfwGetTime() * 6), glm::vec3(1.0f));
		material->getShader()->setMat4("model", model);
		
		glm::mat4 projection = glm::mat4(1.0f);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		material->getShader()->setMat4("projection", projection);
	}
};

