#include <iostream>
#include <string>

#include "LensShader.h"

#include "../Material.h"
#include "LightStructs.h"


namespace ginkgo {

	LensShader::LensShader()
	{
		addVertexShader("Render/res/shaders/lensVertex.vs");
		addFragmentShader("Render/res/shaders/lensFragment.fs");
		compileShader();
	}

	void LensShader::updateUniforms(const glm::mat4& model, const glm::mat4& transformProjectionViewModel, const glm::vec3& cameraPosition) const
	{
		setUniformMat4("model", model);
		setUniformMat4("transform", transformProjectionViewModel);
		setUniform3f("cameraPosition", cameraPosition);
	}

}