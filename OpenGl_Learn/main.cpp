#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "stb_image.h"
#include "Shader.h"
#include "Material.h"
#include "Camera.h"
#include "Cube.h"

const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 600;

void framebufferSize(GLFWwindow* window, int width, int height); 

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

	// Creating shader and material
	Shader *ourShader = new Shader("../ShaderPrograms/vertexShader.vert", "../ShaderPrograms/fragmentShader.frag");
	ourShader->use();
	ourShader->setInt("texture1", 0);

	Material *material = new Material(ourShader);
    material->replaceTextureImage(0, "../Textures/container.jpg", MT_JPG);
	Material* material2 = new Material(ourShader);

	// Add cube and connect with material
	//---------------------------
	Cube cube(0.0f, -0.4f, -3.5f);
	Cube cube2(1.0f, -0.4f, -5.5f);
	cube.setMaterial(material);
	cube2.setMaterial(material2);

	// Activate depth test
	glEnable(GL_DEPTH_TEST);

	glm::mat4 view = glm::mat4(1.0f);
	ourShader->setMat4("view", view);


	// Cicle of render
	//---------------------------
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.3f, 0.5f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader->use();

		cube.draw(window);
		cube2.draw(window);

		cube.setPostition(glm::vec3(0.0f, 0.0f, -4-glfwGetTime()/10.0f));
		cube2.setRotation(glm::vec3(45.0f, glfwGetTime(), glfwGetTime()));

		// ToDo избавиться от изменения перспективы в main
		//-----------------------------
		int widthFrameBuff, heightFrameBuff;
		glm::mat4 projection = glm::mat4(1.0f);
		glfwGetFramebufferSize(window, &widthFrameBuff, &heightFrameBuff);
		projection = glm::perspective(glm::radians(45.0f), (float)widthFrameBuff / (float)heightFrameBuff, 0.1f, 100.0f);
		ourShader->setMat4("projection", projection);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// Вызывается данная функция при изменении размера окна
//-----------------------------
void framebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}