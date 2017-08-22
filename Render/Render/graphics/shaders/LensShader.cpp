#include <iostream>
#include <string>

#include "LensShader.h"

#include "../Material.h"
#include "LightStructs.h"

#include <glm\glm.hpp>

namespace ginkgo {

	LensShader::LensShader()
	{
		addVertexShader("Render/res/shaders/lensVertex.vs");
		addFragmentShader("Render/res/shaders/lensFragment.fs");
		compileShader();

		glGenBuffers(1, &SSBO);
	}

	void LensShader::updateNormals(const std::vector<std::vector<glm::dvec3>>& normals) const
	{
		std::vector<glm::dvec3> data;
		for (int i = 0; i < normals.size(); i++)
				data.insert(std::end(data), std::begin(normals[i]), std::end(normals[i]));

		/*Potentially chagne to uniform*/
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
		glBufferData(GL_SHADER_STORAGE_BUFFER, normals.size() * normals[0].size() * sizeof(glm::dvec3), &data[0], GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		setUniform1i("n", normals.size()); //side length
	}

	void LensShader::updateUniforms(const glm::mat4& model, const glm::mat4& transformProjectionViewModel, const glm::vec3& cameraPosition) const
	{
		setUniformMat4("model", model);
		setUniformMat4("transform", transformProjectionViewModel);
		setUniform3f("cameraPosition", cameraPosition);
	}

}