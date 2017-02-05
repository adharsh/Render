#include "PhongShader.h"

namespace ginkgo {

	PhongShader::PhongShader()
	{
		addVertexShader("Render/res/shaders/phongVertex.vs");
		addFragmentShader("Render/res/shaders/phongFragment.fs");
		compileShader();

		ambientLight = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);

		directionalLight.base.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		directionalLight.base.intensity = 0.0f;
		directionalLight.direction = glm::vec3(0.0f, 0.0f, 0.0f);
	}


	void PhongShader::updateUniforms(glm::mat4& projectionMatrix, Texture& texture)
	{
		if (texture.hasImage())
			texture.bind();
		//else
		//	texture.unbind();
		setUniformMat4("transform", projectionMatrix);
		setUniform4f("baseColor", texture.getColor());
		setUniform4f("ambientLight", ambientLight);

		setUniform("directionalLight", directionalLight);
	}

}