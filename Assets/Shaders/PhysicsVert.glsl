#version 400 core

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);


layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;	
layout(location = 2) in vec2 texCoord;
//layout(location = 3) in vec3 velocity;

out Vertex 
{
	vec3 position;
	vec4 colour;
	vec2 texCoord;
	
} OUT;

	
void main(void)
{
	
	vec3 new_position = position;
	//new_position.y = new_position.y - 3;
	
	//if(new_position.y < 10.0)
	//{
		//new_position.y = new_position.y +60;
	//}
	mat4 mvp 		= (projMatrix * viewMatrix * modelMatrix);
	
	gl_Position		= mvp * vec4(new_position, 1.0);
	OUT.position	= new_position;
	OUT.colour		= colour;
	OUT.texCoord	= texCoord;
	
}