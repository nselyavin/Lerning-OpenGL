#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "stb_image.h"
#include "Shader.h"

void framebufferSize(GLFWwindow* window, int width, int height); 
void processInput(GLFWwindow * window);

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

	// Создание текстуры 1
	//--------------------------
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nrCompenents;
	stbi_set_flip_vertically_on_load(true); 
	unsigned char* data =  stbi_load("../Textures/container.jpg", &width, &height, &nrCompenents, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed image load\n";
	}
	stbi_image_free(data);

	// Загрузка текстуры 2
	GLuint texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width2, height2, nrComponents2;
	// Чтобы изображение загружалось перевернутым, так как OpenGL ожидает что координата 0.0 
	//на оси Y будет находиться в нижней части изображения, но изображения обычно имеют 0.0 в верхней части оси Y
	data = stbi_load("../Textures/poni.jpg", &width, &height, &nrComponents2, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load image\n";
	}

	// Инициализация вершин
	//---------------------------
	float vertices[] = {
		-0.7f,  0.7f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // В-Л
		 0.7f,  0.7f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,  // В-П
		 0.7f, -0.7f, 0.0f,  0.0f, 0.0f, 1.0f,	1.0f, 0.0f,  // Н-П
		-0.7f, -0.7f, 0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f   // Н-Л
	};

	GLuint indiceis[] = {
		0, 1, 2,
		3, 2, 0
	};
	
	// Генерацию буферов
	GLuint VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// сначала связываем объект вершинного массива, затем связываем и устанавливаем вершинный буфер(ы), и затем конфигурируем вершинный атрибут(ы).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indiceis), indiceis, GL_STATIC_DRAW);

	// Координатный атрибут
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Цветовой атрибут
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Текстурный атрибут
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	int invert = 0;
	float opacity = 0.0, opacity2 = 0.0;
	ourShader.setFloat("opacity", opacity);
	ourShader.setFloat("opacity2", opacity2);
	ourShader.setInt("invert", invert);

	// Цикл рендера
	//---------------------------
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		srand(glfwGetTimerValue());
		opacity = rand() % 2;
		ourShader.setFloat("opacity", opacity);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			invert = 1;
			ourShader.setInt("invert", invert);
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			invert = 0;
			ourShader.setInt("invert", invert);
		}

		glClearColor(0.3f, 0.5f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.use();
		glBindVertexArray(VAO); 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Данная функция сама наложит текстуру на наш элемент

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Освобождение ресурсов (опционально)
	//------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

// Вызывается данная функция при изменении размера окна
//-----------------------------
void framebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Обработка событий ввода
//-----------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}