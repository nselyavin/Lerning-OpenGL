#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

#include "stb_image.h"
#include "Shader.h"
#include "Material.h"
#include "Camera.h"
#include "Cube.h"

void framebufferSize(GLFWwindow* window, int width, int height); 

const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 600;


int main() 
{
	// Инициализация и конфигурирование
	//-------------------------------
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	// Создание окна
	// ------------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "main", NULL, NULL);
	if (!window) {
		std::cout << "WINDOW::CREATE::FAILED\n";
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSize);

	// Загрузка указателей 
	//-------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD::LOADGL::FAILED\n";
		glfwTerminate();
		return -1;
	}

	// Привязка и компиляция шейдеров
	//--------------------------------
	Shader ourShader("../ShaderPrograms/vertexShader.vert", "../ShaderPrograms/fragmentShader.frag");
	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	Material* cubeMaterial = new Material(&ourShader);
	cubeMaterial->loadTexture("../Textures/container.jpg", MT_JPG);
	cubeMaterial->loadTexture("../Textures/poni.jpg", MT_JPG);

	Cube cube;
	cube.setMaterial(cubeMaterial);

	// Цикл рендера
	//---------------------------
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.3f, 0.5f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Освобождение ресурсов (опционально)
	//------------------------

	glfwTerminate();
	return 0;
}

// Вызывается данная функция при изменении размера окна
//-----------------------------
void framebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}