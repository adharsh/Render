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

	void LensShader::updateNormals(const std::vector<std::vector<glm::dvec4>>& normals) const
	{
		/*glm::dvec4 data[4] =
		{
		glm::dvec4(1, 0, 0, 0),
		glm::dvec4(0, 1, 0, 0),
		glm::dvec4(0, 0, 1, 0),
		glm::dvec4(1, 1, 1, 0)
		};
		*/
		//std::vector<glm::dvec4> data;
		//data.emplace_back(glm::dvec4(1, 0, 0, 0));
		//data.emplace_back(glm::dvec4(0, 1, 0, 0));
		//data.emplace_back(glm::dvec4(0, 0, 1, 0));
		//data.emplace_back(glm::dvec4(1, 1, 1, 0));

		///*Potentially chagne to uniform*/
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
		//glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(glm::dvec4), &data[0], GL_DYNAMIC_DRAW);
		//glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, SSBO);
		//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

		std::vector<glm::dvec4> data;
		for (int i = 0; i < normals.size(); i++)
			data.insert(std::end(data), std::begin(normals[i]), std::end(normals[i]));
		/*Potentially chagne to uniform*/
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
		glBufferData(GL_SHADER_STORAGE_BUFFER, normals.size() * normals[0].size() * sizeof(glm::dvec4), &data[0], GL_STATIC_DRAW);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, SSBO);
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