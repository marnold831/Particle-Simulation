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
	vec3 particlePosition;
} OUT;

	
void main(void)
{
	
	vec3 new_position = vec3(position.x, position.y - 5, position.z);
	
	//if(new_position.y < 10.0)
	//{
	//	new_position = (new_position.x, new_position.y + 60, new_position.z);
	//}
	mat4 mvp 		= (projMatrix * viewMatrix * modelMatrix);
	
	gl_Position		= mvp * vec4(new_position, 1.0);

	out_colour		= colour;
	out_texCoord	= texCoord;
	particlePosition = new_position;
	
}