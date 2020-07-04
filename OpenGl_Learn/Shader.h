#pragma once

#include <glad/glad.h>

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

private:
	void checkCompileError(GLuint shader, typei type);
};

