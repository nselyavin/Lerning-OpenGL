#include "Geometry.h"

Geometry::Geometry() {
	VBO = 0;
	VAO = 0;
	p_material = nullptr;
	position = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
}

Geometry::Geometry(float posx, float posy, float posz) {
	VBO = 0;
	VAO = 0;
	p_material = nullptr;
	position = glm::vec3(posx, posy, posz);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}


void Geometry::setMaterial(Material* material) {
	this->p_material = material;
}

void Geometry::setPostition(glm::vec3 position)
{
	this->position = position;
}

void Geometry::setRotation(glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Geometry::setScale(glm::vec3 scale)
{
	this->scale = scale;
}

Material* Geometry::getMaterial()
{
	return p_material;
}

Geometry::~Geometry() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Geometry::acceptTransform(GLFWwindow* window) {
	if (p_material) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);
		
		model *= glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
		p_material->getShader()->setMat4("model", model);
	}
	else {
		std::cout << "WARNING::GEOMETRY::NOTFOUND_MATERIAL\n";
	}
}

