#version 400 core

uniform sampler2D mainTex;

	in vec4 colour;
	in vec2 texCoord;


	out vec4 fragColor;

void main(void)
{	
	if(textureSize(mainTex, 1).x < 1.0f) {
		fragColor = colour;
	}
	else {
		fragColor = texture(mainTex, texCoord);// * colour;
	}
}