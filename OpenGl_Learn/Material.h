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
	// Set gl texture parametr
	void setTextureParametr(GLuint texture, GLuint pname, GLuint value);

	// Bind all textures in array to texture unit
	void activateTexture(GLFWwindow *window);
	
	std::vector <GLuint>& getTexturesVec();
	size_t getAmountTextures();
	Shader* getShader();
};

