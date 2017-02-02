#version 330 
precision highp float;

in vec4 color;

out vec4 fragColor;

void main()
{
	//fragColor = color;
	fragColor = color; //vec4(1.0, 1.0, 1.0, 1.0); 
}