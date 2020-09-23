#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "glm/gtc/type_ptr.hpp"

#include "stb_image.h"
#include "Shader.h"

#define MT_PNG GL_RGBA
#define MT_JPG GL_RGB

const int MAX_TEXTURES = 16;

class Material
{
	Shader* shader;
	std::vector <GLuint> textures;

public:
	Material(Shader *shader);

	// load texture to matirial. Will adding into textures array
	void loadTexture(const char* path, GLuint format = MT_JPG);
	void replaceTextureImage(GLuint texturePos, const char* path, GLuint format = MT_JPG);
	// Set gl texture parametr
	void setTextureParametr(GLuint texturePos, GLuint pname, GLuint value);

	// Bind all textures in array to texture unit
	void activateTexture(GLFWwindow *window);
	
	std::vector <GLuint>& getTexturesVec();
	size_t getAmountTextures();
	Shader* getShader();

private:
	void bindAndSetUpTexture(GLuint texture, const char* path, GLuint format) {
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
	}
};

