#version 330 
precision highp float;

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 normal;

out vec2 texCoord;
out vec3 normalCoord;

uniform mat4 transform;
uniform mat4 model;

void main()
{
	gl_Position = transform * vec4(position, 1.0f);
	texCoord = texture;
	normalCoord = (transform * vec4(normal, 0.0)).xyz;
}