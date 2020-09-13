/*
	Класс описывающий работу шейдеров.
	Примает исходный код шейдерной программы и на его основе создает шейдеры и шейдерную программу.
	Хранит ID шейдерную программу.
	Может устанавливать текущий шейдер используемым
*/

#pragma once

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define VERTEX 0
#define FRAGMENT 1
#define PROGRAM 2

using typei = int;

class Shader
{
public:
	// Идентификатор программы 
	GLuint id;

	// Считывает данные и выполняет настройки шейдера
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;

private:
	void checkCompileError(GLuint shader, typei type);
};

