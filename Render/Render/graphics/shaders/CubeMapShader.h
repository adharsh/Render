#pragma once

#include <glm/glm.hpp>

#include "Shader.h"

namespace ginkgo {
	

	class CubeMapShader : public Shader
	{
	public:
		CubeMapShader();
		void updateUniforms(const glm::mat4& projectionMatrix);
	};


}