#include "Material.h"

Material::Material(Shader* shader)
{
	this->shader = shader;
	textures.resize(0);
	loadTexture("../Textures/DefaultUV.jpg", MT_JPG);
}

void Material::loadTexture(const char* path, GLuint format)
{
	if (textures.size() <= MAX_TEXTURES) {
		GLuint texture;
		glGenTextures(1, &texture);
		bindAndSetUpTexture(texture, path, format);
		textures.push_back(texture);
	}
	else {
		std::cout << "WARNING::TEXTURE_STACK_OVERFLOW\n";
	}
}

void Material::replaceTextureImage(GLuint texturePos, const char* path, GLuint format)
{
	bindAndSetUpTexture(textures[texturePos], path, format);
}



std::vector <GLuint>& Material::getTexturesVec() {
	return textures;
}

size_t Material::getAmountTextures()
{
	return textures.size();
}

Shader* Material::getShader()
{
	return shader;
}

void Material::setTextureParametr(GLuint texturePos, GLuint pname, GLuint value)
{
	glBindTexture(GL_TEXTURE_2D, textures[texturePos]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}


void Material::activateTexture(GLFWwindow* window)
{
	
	for (size_t i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
	}
	shader->use();
	
}