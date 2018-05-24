#version 430
precision highp float;

in vec3 worldPos;
in vec2 texCoord;

out vec4 fragColor;

uniform vec3 cameraPosition;
uniform samplerCube skybox;

//uniform int n;
#define N 512

 layout(std430, binding = 2) buffer normal_data
 {
     dvec4 data[N][N];
 };

 //#define test 1

void main()
{
	fragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	//#if test
	int r = int( (N-1)*(1-texCoord.y));
	int c = int( (N-1)*texCoord.x);
	int a = 1;
	if(r == (N-1)) r = (N-1) - a;
	if(c == (N-1)) c == (N-1) - a;
	dvec3 Normal = normalize(data[r][c] + data[r + a][c] + data[r][c + a]).xyz;
	
	//Below is wrong, just skybox needs to be as detailed as possible, but lensing needs to be less pixelated, check with N with 16 for ex
	//TODO: its not the normal data thats being pixelated, its the actual skybox image that is pixelated
	//somehow linearly interpolate the samplerCube skybox

	//#else 
	//dvec3 Normal = data[int( (N-1)*(1-texCoord.y)+0.5 )][int( (N-1)*texCoord.x + 0.5 )].xyz;
	//#endif

	dvec3 Incident = normalize(worldPos - cameraPosition);
	//dvec3 R = refract(Incident, Normal, 1.0f/2.0f); //1/refractive index -> 1.0f/2.0f, refractive index in vacuum is 1.0
	dvec3 R = refract(Incident, Normal, 1.0f/2.0f); //1/refractive index -> 1.0f/2.0f
	
	fragColor = texture(skybox, vec3(R));

	//fragColor = vec4(Normal, 1.0);
}