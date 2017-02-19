#pragma once

#include <glm\glm.hpp>

namespace ginkgo {

	typedef struct BaseLight {
		glm::vec4 color;
		float intensity;
		BaseLight() {}
		BaseLight(glm::vec4& colorBL, float intensityBL) : color(colorBL), intensity(intensityBL) {}
	} BaseLight;

	typedef struct DirectionalLight {
		BaseLight base;
		glm::vec3 direction;
		DirectionalLight() {}
		DirectionalLight(BaseLight& baseDL, glm::vec3& directionDL) : base(baseDL), direction(directionDL) {}
	} DirectionalLight;

	typedef struct Attenuation {
		float constant;
		float linear;
		float quadratic;
		Attenuation() {}
		Attenuation(float constantA, float linearA, float quadraticA) : constant(constantA), linear(linearA), quadratic(quadraticA) {}
	} Attenuation;

	typedef struct PointLight {
		BaseLight base;
		Attenuation attenuation;
		glm::vec3 position;
		PointLight() {}
		PointLight(BaseLight& basePL, Attenuation& attenuationPL, glm::vec3& positionPL) : base(basePL), attenuation(attenuationPL), position(positionPL) {}
	} PointLight;

}