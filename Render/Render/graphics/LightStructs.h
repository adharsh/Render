#pragma once

#include <glm\glm.hpp>

namespace ginkgo {

	typedef struct BaseLight
	{
		glm::vec4 color;
		float intensity;
	} BaseLight;

	typedef struct DirectionalLight
	{
		BaseLight base;
		glm::vec3 direction;
	} DirectionalLight;

}