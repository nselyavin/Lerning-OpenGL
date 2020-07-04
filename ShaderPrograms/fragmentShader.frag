#version 330 core

out vec4 color;

in vec3 ourPosition;
//in vec3 ourColor;

void main()
{
	color = vec4(ourPosition, 1.0f);

}