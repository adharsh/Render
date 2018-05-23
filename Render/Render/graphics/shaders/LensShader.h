#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"

namespace ginkgo {

	class Material;

	class LensShader : public Shader
	{
	private:
		GLuint SSBO;
	public:
		LensShader();
		void updateNormals(const std::vector<std::vector<glm::dvec4>>& normals) const;
		void updateUniforms(const glm::mat4& model, const glm::mat4& transformProjectionViewModel, const glm::vec3& cameraPosition) const;
	};

}