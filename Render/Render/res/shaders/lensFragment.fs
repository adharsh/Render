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

 layout(std430, binding = 0) buffer normal_data
 {
     dvec3 data[n][n];
 } normals;

void main()
{
	fragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	//vec3 Normal = vec3(0, texture(normalMap, texCoord).y, 0);
	//vec3 Normal = vec3(texture(normalMap, texCoord).x, 0, 0);
	//vec3 Normal = vec3(0, 0, texture(normalMap, texCoord).z);
	
	dvec3 Normal = normals.data[int(n*(1-(texCoord.y)))][int(n*(texCoord.x))];
	//Normal = normals.data[0][0];
	dvec3 Incident = normalize(worldPos - cameraPosition);
	dvec3 R = refract(Incident, Normal, 1.0f/2.0f); //1/refractive index -> 1.0f/2.0f
	fragColor = texture(skybox, vec3(R));
	//fragColor = texture(normalMap, texCoord);
	//fragColor  = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//fragColor  = vec4(Normal,1);
	//fragColor  = vec4(texCoord.x, texCoord.y, 0.0f, 0.0f);
}
