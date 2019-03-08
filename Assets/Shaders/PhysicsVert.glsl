#version 420 core

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);


layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;	
layout(location = 2) in vec2 texCoord;

out Vertex
{
	vec4 colour;
	vec2 texCoord;
} OUT;

out vec4 newPos;
void main(void)
{
	
	vec4 new_position = vec4(position.x, position.y - 5, position.z, 1.0);
	
	if(new_position.y < 10.0)
	{
		new_position = vec4(new_position.x, position.y + 60, position.z, 1.0);
	}
	mat4 mvp 		= (projMatrix * viewMatrix * modelMatrix);
	newPos = new_position;
	gl_Position		= mvp * new_position;

	OUT.colour		= colour;
	OUT.texCoord	= texCoord;
	
}