#pragma once

#include <glm/glm.hpp>
#include "Shader.h"

namespace ginkgo {

	class Texture;
	class Material;

	class BasicShader : public Shader
	{
	public:
		BasicShader();
		void updateUniforms(const glm::mat4& projectionMatrix, const Material& material);
	};


}