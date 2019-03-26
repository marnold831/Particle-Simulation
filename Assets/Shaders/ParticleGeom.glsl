#version 330 core

uniform float particleSize = 0.5f;

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;


	in vec4[] colour;
	in vec2[] texCoord;


	out vec4 out_colour;
	out vec2 out_texCoord;


void main() {

	for(int i =0; i < gl_in.length(); ++i) {
		out_colour = colour[i];
		// top right
		gl_Position = gl_in[i].gl_Position;
		gl_Position.x += particleSize;
		gl_Position.y += particleSize;
		out_texCoord = vec2(1, 0);
		
		EmitVertex();
		
		// Top Left
		gl_Position = gl_in[i].gl_Position;
		gl_Position.x -= particleSize;
		gl_Position.y += particleSize;
		out_texCoord = vec2(0, 0);
		EmitVertex();
		
		// bottom right
		gl_Position = gl_in[i].gl_Position;
		gl_Position.x += particleSize;
		gl_Position.y -= particleSize;
		out_texCoord = vec2(1, 1);
		EmitVertex();
		
		// bottom Left
		gl_Position = gl_in[i].gl_Position;
		gl_Position.x -= particleSize;
		gl_Position.y -= particleSize;
		out_texCoord = vec2(0, 1);
		EmitVertex();
		
		EndPrimitive();

	}
}