#version 330 core
precision highp float;

in vec3 Normal;
in vec3 Position;

out vec4 color;

uniform vec3 cameraPosition;
uniform samplerCube skybox;

void main()
{   
	float ratio = 1.0f / 0.99f;
    vec3 Incident = normalize(Position - cameraPosition );
//    vec3 R = reflect(Incident, normalize(Normal));
	vec3 R = refract(Incident, normalize(Normal), ratio);
	
	
	color = texture(skybox, R);
}