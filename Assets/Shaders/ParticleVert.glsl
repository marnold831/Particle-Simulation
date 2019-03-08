#version 420 core

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);


layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;	
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

out Vertex
{
	vec4 world_space_matrix;
	vec3 vs_fs_normal;
	vec4 colour;
	vec2 texCoord;
} OUT;

void main(void)
{
	ce4 pos = (modelMatrix* (position * vec4(1.0, 1.0, 1.0, 1.0)));
	world_space_matrix = pos;
	vs_fs_normal = normalize((modelMatrix * vec4(normal, 0.0)).xyz);
	gl_Position = projMatrix * pos;
}