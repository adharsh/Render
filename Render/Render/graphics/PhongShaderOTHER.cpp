#include "PhongShader.h"

namespace ginkgo {
	
	glm::vec4 PhongShader::ambientLight = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	
	PhongShader::PhongShader()
	{

		addVertexShader("Render/res/shaders/phongVertex.vs");
		addFragmentShader("Render/res/shaders/fragmentshader.fs");
		compileShader();
	}

	void PhongShader::updateUniforms(glm::mat4& projectionMatrix, Texture& texture, glm::vec4& ambient)
	{
		if (texture.hasImage())
			texture.bind();
		//else
		//	texture.unbind();

		setUniformMat4("transform", projectionMatrix);
		setUniform4f("baseColor", texture.getColor());
		setUniform4f("ambientLight", ambient);
	}

}