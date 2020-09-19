#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;

void main()
{
	vec4 texColor = texture(texture1, TexCoord);
    FragColor = vec4(TexCoord, 0.3f, 1.0f) ;
}