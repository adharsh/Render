#pragma once

#include <string>

#include "Shader.h"
#include "Texture.h"

namespace ginkgo {

	class BasicShader : public Shader
	{
	public:
		BasicShader();
		void updateUniforms(glm::mat4& projectionMatrix, Texture& texture);
	};


}