#include "Material.h"

Material::Material(Shader* shader)
{
	this->shader = shader;
	textures.resize(0);
}

void Material::loadTexture(const char* path, GLuint format)
{
	if (textures.size() <= MAX_TEXTURES) {
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrComponents;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "ERROR::MATERIAL::IMAGE::FAILED_LOAD\n";
		}

		stbi_image_free(data);
		textures.push_back(texture);
	}
	else {
		std::cout << "WARNING::TEXTURE_STACK_OVERFLOW\n";
	}
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

void Material::setTextureParametr(GLuint index, GLuint pname, GLuint value)
{
	glBindTexture(GL_TEXTURE_2D, textures[index]);
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