#version 330 
precision highp float;

in vec2 texCoord;

uniform vec4 color;
uniform sampler2D sampler;

void main()
{
	vec4 textureColor = texture2D(sampler, texCoord.xy);

	if(textureColor == 0) //TODO: this doesnt work
		gl_FragColor = color;
	else
		gl_FragColor = textureColor * color;
}