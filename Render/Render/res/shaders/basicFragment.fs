#version 330 
precision highp float;

in vec4 color;
in vec2 texCoord;

uniform sampler2D sampler;

void main()
{
	//fragColor = color; //vec4(1.0, 1.0, 1.0, 1.0); 
	//gl_FragColor = color;
	gl_FragColor = texture2D(sampler, texCoord.xy) * color;
	//fragColor = color * texture(textureImage, texCoordd);

}