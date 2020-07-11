#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec4 texColor = texture(texture2, TexCoord);
    FragColor = mix(texture(texture1, TexCoord), texColor, 0.5);
	
}