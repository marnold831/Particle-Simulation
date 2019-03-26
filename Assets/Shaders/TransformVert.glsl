#version 400 core

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;	
layout(location = 2) in vec2 texCoord;



	out vec4 out_colour;
	out vec2 out_texCoord;
	out vec3 particlePosition;
void main(void)
{
	mat4 mvp 		= (projMatrix * viewMatrix * modelMatrix);

	gl_Position		= mvp * vec4(position, 1.0);

	
	out_colour		= colour;
	out_texCoord	= texCoord;
	
	particlePosition = position;
	
}