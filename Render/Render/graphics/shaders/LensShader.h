#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

namespace ginkgo {

	class Material;

	class LensShader : public Shader
	{
	public:
		LensShader();
		void updateUniforms(const glm::mat4& model, const glm::mat4& transformProjectionViewModel, const glm::vec3& cameraPosition) const;
	};


}