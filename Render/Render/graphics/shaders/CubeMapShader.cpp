#include "CubeMapShader.h"

namespace ginkgo {

	CubeMapShader::CubeMapShader()
	{
		addVertexShader("Render/res/shaders/cubemapVertex.vs");
		addFragmentShader("Render/res/shaders/cubemapFragment.fs");
		compileShader();
	}

	void CubeMapShader::updateUniforms(const glm::mat4& projectionMatrix)
	{
		setUniformMat4("transform", projectionMatrix);
	}

}