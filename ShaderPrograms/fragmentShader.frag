  
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float opacity;
uniform float opacity2;
uniform int invert;

void main()
{
	
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(abs(invert - TexCoord.x), TexCoord.y)), opacity);
	//FragColor += vec4(ourColor, 1.0f) * opacity2;
}