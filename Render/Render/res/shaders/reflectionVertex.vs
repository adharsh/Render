#version 330 
precision highp float;

layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 normal;
layout (location = 1) in vec2 uvs;
layout (location = 2) in vec3 normal;

out vec3 Normal;
out vec3 Position;

uniform mat4 transform;
uniform mat4 model;

void main()
{
	gl_Position = transform * vec4(position, 1.0f);
	Normal = mat3(transpose(inverse(model))) * normal;
	Position = vec3(model * vec4(position, 1.0f));
}