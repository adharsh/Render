#version 430
precision highp float;

in vec3 worldPos;
in vec2 texCoord;

out vec4 fragColor;

uniform vec3 cameraPosition;
//uniform sampler2D normalMap;
uniform samplerCube skybox;
//uniform int n;
#define n 510

 layout(std430, binding = 2) buffer normal_data
 {
     dvec4 data[n][n];
 };

void main()
{
	fragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	dvec3 Normal = data[int( (n-1)*(1-texCoord.y)+0.5 )][int( (n-1)*texCoord.x + 0.5 )].xyz;
	//dvec3 Normal = data[n * int( (n-1)*(1-texCoord.y)+0.5 ) + int( (n-1)*texCoord.x + 0.5 )].xyz; 

	//(n-1) * (1-texCoord.y) * n + (n-1) *x 

	//Normal = data[0][0].xyz;
	//dvec3 Normal = data[2].xyz;
	dvec3 Incident = normalize(worldPos - cameraPosition);
	dvec3 R = refract(Incident, Normal, 1.0f/2.0f); //1/refractive index -> 1.0f/2.0f
	fragColor = texture(skybox, vec3(R));

//	if(	int((n-1) * (1-texCoord.y) * n + (n-1) * texCoord.x) == 0 )
//		fragColor = vec4(1, 0, 0, 1);
//	else if (int((n-1) * (1-texCoord.y) * n + (n-1) * texCoord.x) == 1)
//		fragColor = vec4(0, 1, 0, 1);
//	else if (int((n-1) * (1-texCoord.y) * n + (n-1) * texCoord.x) == 2)
//		fragColor = vec4(0, 0, 1, 1);
//	else if (int((n-1) * (1-texCoord.y) * n + (n-1) * texCoord.x) == 3)
//		fragColor = vec4(0, 0, 0, 1);
	
	//fragColor = vec4(texCoord.x, texCoord.y, 0.0f, 0.0f);
	//
	//fragColor  = vec4(Normal,1);
	//fragColor  = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
