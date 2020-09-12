#include "Cube.h"

Cube::Cube(): Geometry(){}

Cube::Cube(float posx, float posy, float posz) : Geometry(posx, posy, posz) 
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Cube::draw()
{

}
