#version 330 
precision highp float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;

out vec4 color;
uniform mat4 transform;

void main()
{
	
	color = vec4(clamp(position, 0.0f, 1.0f), 1.0f);
	//color = vec4(position, 1.0f);
	gl_Position = transform * vec4(position, 1.0f);

}