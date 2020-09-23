#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "Material.h"

class Geometry
{
protected:
	GLuint VBO, VAO;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	Material* p_material;

public:
	// Geometry construct, set standart transform value
	Geometry();
	// Geometry construct, set user position value
	Geometry(float posx, float posy, float posz);

	// Function of geometry drawing, must be overloaded in instance class
	virtual void draw(GLFWwindow* window) = 0;

	// Changing geometry's material
	void setMaterial(Material* material);

	void setPostition(glm::vec3 position);
	void setRotation(glm::vec3 rotation);
	void setScale(glm::vec3 scale);

	// Get access to geometry material
	Material* getMaterial();

	~Geometry();

protected:
	void acceptTransform(GLFWwindow* window);
};

