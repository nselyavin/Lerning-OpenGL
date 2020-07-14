#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// Считываем шейдеры из файла
	//----------------------------
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream vFragmentFile;

	// Убеждаемся, что объекты могу выбросить исключение
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	vFragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		vFragmentFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << vFragmentFile.rdbuf();

		vShaderFile.close();
		vFragmentFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderSource = vertexCode.c_str();
	const char* fShaderSource = fragmentCode.c_str();

	// Компилируем шейдеры
	//-----------------------------
	GLuint vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderSource, NULL);
	glCompileShader(vertex);
	checkCompileError(vertex, VERTEX);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderSource, NULL);
	glCompileShader(fragment);
	checkCompileError(fragment, FRAGMENT);

	// Создаем шейдерную программу
	//--------------------------------
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	checkCompileError(id, PROGRAM);

	// Шейдеры больше не нужны
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	int loc = glGetUniformLocation(id, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::checkCompileError(GLuint shader, typei type)
{
	int success;
	char infoLog[512];

	if (type != PROGRAM) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			if (type == VERTEX)
				std::cout << "ERROR::SHADER::VERTEX::COMPILE::FAILED >> " << infoLog;
			else 
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILE::FAILED >> " << infoLog;
		}
	}
	else if (type == PROGRAM) {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::PROGRAM::LINK::FAILED >> " << infoLog;
		}
	}
}


/*// Считываем шейдеры из файла
	//----------------------------
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream vFragmentFile;

	// Убеждаемся, что объекты могу выбросить исключение
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	vFragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		vFragmentFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		vShaderStream << vFragmentFile.rdbuf();

		vShaderFile.close();
		vFragmentFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const char* vShaderSource = vertexCode.c_str();
	const char* fShaderSource = fragmentCode.c_str();

	// Компилируем шейдеры
	//-----------------------------
	GLuint vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderSource, NULL);
	glCompileShader(vertex);
	checkCompileError(vertex, SHADER);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderSource, NULL);
	glCompileShader(fragment);
	checkCompileError(fragment, SHADER);

	// Создаем шейдерную программу
	//--------------------------------
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	checkCompileError(id, PROGRAM);

	// Шейдеры больше не нужны
	glDeleteShader(vertex);
	glDeleteShader(fragment);*/