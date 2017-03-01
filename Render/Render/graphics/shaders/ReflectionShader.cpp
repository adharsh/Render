#include "ReflectionShader.h"

#include "../Material.h"

namespace ginkgo {

	ReflectionShader::ReflectionShader()
	{
		addVertexShader("Render/res/shaders/reflectionVertex.vs");
		addFragmentShader("Render/res/shaders/reflectionFragment.fs");
		compileShader();
	}

	void ReflectionShader::updateUniforms(const glm::mat4& model, const glm::mat4& projectioViewMatrix, const glm::vec3& cameraPosition) const
	{
		setUniformMat4("model", model);
		setUniformMat4("transform", projectioViewMatrix);
		setUniform3f("cameraPosition", cameraPosition);
	}

}