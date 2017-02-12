#version 330 
precision highp float;

const int MAX_POINT_LIGHTS = 4;

in vec2 texCoord;
in vec3 normalCoord;
in vec3 worldPos;

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

struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};

struct PointLight
{
	BaseLight base;
	Attenuation attenuation;
	vec3 position;
};

uniform vec4 baseColor;
uniform vec4 ambientLight;
uniform sampler2D sampler;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform vec3 eyePos;
uniform float specularIntensity;
uniform float specularPower;


vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
	float diffuseFactor = dot(normal, -direction);

	vec4 diffuseColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	vec4 specularColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	if(diffuseFactor > 0)
	{
		diffuseColor = base.color * base.intensity * diffuseFactor;

		vec3 directionToEye = normalize(eyePos - worldPos);
		vec3 reflectDirection = normalize(reflect(direction, normal));

		float specularFactor = dot(directionToEye, reflectDirection);
		specularFactor = pow(specularFactor, specularPower);

		if(specularFactor > 0)
		{
			specularColor = base.color * specularIntensity * specularFactor;
		}

	}

	return diffuseColor + specularColor;
}

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calcLight(directionalLight.base, -directionalLight.direction, normal);
}

vec4 calcPointLight(PointLight pointLight, vec3 normal)
{
	vec3 lightDirection = worldPos - pointLight.position;
	float distanceToPoint = length(lightDirection);
	lightDirection = normalize(lightDirection);

	vec4 color = calcLight(pointLight.base, lightDirection, normal);
	
	float attenuation = pointLight.attenuation.constant + 
						 pointLight.attenuation.linear * distanceToPoint + 
						 pointLight.attenuation.quadratic * distanceToPoint * distanceToPoint
						 + 0.0001;
	return 15.0f * color / attenuation; 
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

	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
		totalLight += calcPointLight(pointLights[i], normal);

	fragColor = color * totalLight;
	//fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}