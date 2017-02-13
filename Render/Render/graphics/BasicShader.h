#pragma once

#include <string>

#include "Shader.h"
#include "Texture.h"

namespace ginkgo {

	class BasicShader : public Shader
	{
	public:
		BasicShader();
		void updateUniforms(const glm::mat4& projectionMatrix, Texture& texture);
	};


}