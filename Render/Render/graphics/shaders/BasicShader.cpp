#include "BasicShader.h"

#include "../Texture.h"

namespace ginkgo {

	BasicShader::BasicShader()
	{
		addVertexShader("Render/res/shaders/vertexshader.vs");
		addFragmentShader("Render/res/shaders/fragmentshader.fs");
		compileShader();
	}

	void BasicShader::updateUniforms(const glm::mat4& projectionMatrix, const Texture& texture)
	{
		setUniformMat4("transform", projectionMatrix);
		setUniform4f("color", texture.getColor());
	}

}