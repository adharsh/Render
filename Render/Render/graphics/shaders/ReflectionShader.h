#pragma once

#include <glm/glm.hpp>
#include "Shader.h"

namespace ginkgo {

	class ReflectionShader : public Shader
	{
	public:
		ReflectionShader();
		void updateUniforms(const glm::mat4& model, const glm::mat4& projectioViewMatrix, const glm::vec3& cameraPosition) const;
	};


}