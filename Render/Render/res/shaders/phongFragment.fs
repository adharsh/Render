#version 330 
precision highp float;

in vec2 texCoord;
in vec3 normalCoord;

out vec4 fragColor;


struct BaseLight
{
	vec4 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

uniform vec4 baseColor;
uniform vec4 ambientLight;
uniform sampler2D sampler;

uniform DirectionalLight directionalLight;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);

	vec4 diffuseColor  = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	if(diffuseFactor > 0)
	{
		diffuseColor = base.color * base.intensity * diffuseFactor;
	}

	return diffuseColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calcLight(directionalLight.base, -directionalLight.direction, normal);
}


void main()
{
	vec4 totalLight = ambientLight;
	vec4 color = baseColor;
	vec4 textureColor = texture(sampler, texCoord.xy);

	if(textureColor != vec4(0.0f, 0.0f, 0.0f, 0.0f))
		color *= textureColor;
	
	vec3 normal = normalize(normalCoord); //TODO: gaureentte its already normalized, so in the future take out this code

	totalLight += calcDirectionalLight(directionalLight, normal);

	fragColor = color * totalLight;
}