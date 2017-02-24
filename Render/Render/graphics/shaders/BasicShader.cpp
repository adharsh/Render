#include "BasicShader.h"

#include "../Material.h"

namespace ginkgo {

	BasicShader::BasicShader()
	{
		addVertexShader("Render/res/shaders/vertexshader.vs");
		addFragmentShader("Render/res/shaders/fragmentshader.fs");
		compileShader();
	}

	void BasicShader::updateUniforms(const glm::mat4& projectionMatrix, const Material& material)
	{
		setUniformMat4("transform", projectionMatrix);
		setUniform4f("color", material.getColor());
	}

}