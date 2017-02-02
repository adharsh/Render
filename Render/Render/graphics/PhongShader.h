#pragma once

#include <string>

#include "Shader.h"
#include "Texture.h"

namespace ginkgo {

	class PhongShader : public Shader
	{
	private:
		//glm::vec4 ambientLight = glm::vec4(0.1f, 0.1f, 0.1f, 0.1f);
		glm::vec4 ambientLight;
		//DirectionalLight directionalLight = { .base = {.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), .intensity = 0 }, .direction = glm::vec3(1.0f, 1.0f, 1.0f) };
		DirectionalLight directionalLight;
	public:
		PhongShader();
		void updateUniforms(glm::mat4& projectionMatrix, Texture& texture);

		inline glm::vec4& getAmbientLight() { return ambientLight; }
		inline void setAmbientLight(const glm::vec4& ambientLight) { this->ambientLight = ambientLight; }


		inline DirectionalLight& getDirectionalLight() { return directionalLight; }
		inline void setDirectionalLight(const DirectionalLight& directionalLight) { this->directionalLight = directionalLight; }
	};


}