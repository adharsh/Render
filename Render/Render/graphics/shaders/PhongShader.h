#pragma once

#include <string>

#include "Shader.h"
#include "../Texture.h"
#include "LightStructs.h"

namespace ginkgo {

	class PhongShader : public Shader
	{
	private:
		//glm::vec4 ambientLight = glm::vec4(0.1f, 0.1f, 0.1f, 0.1f);
		glm::vec4 ambientLight; //should be static
		//DirectionalLight directionalLight = { .base = {.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), .intensity = 0 }, .direction = glm::vec3(1.0f, 1.0f, 1.0f) };
		DirectionalLight directionalLight; //should be static
		const int MAX_POINT_LIGHTS = 4;
		std::vector<PointLight> pointLights;
		
	public:
		PhongShader();
		void updateUniforms(const glm::mat4& model, const glm::mat4& projectionMatrix, const Texture& texture, const glm::vec3& cameraPosition) const;

		const glm::vec4& getAmbientLight() const { return ambientLight; }
		void setAmbientLight(const glm::vec4& ambientLight) { this->ambientLight = ambientLight; }

		void setPointLights(const std::vector<PointLight>& pointLights);
		void setPointLightPosition(unsigned int index, const glm::vec3& position);

		const DirectionalLight& getDirectionalLight() const { return directionalLight; }
		void setDirectionalLight(const DirectionalLight& directionalLight);
		
		void setUniform(const std::string& name, const DirectionalLight& directionalLight) const;
		void setUniform(const std::string& name, const BaseLight& baseLight) const;
		void setUniform(const std::string& name, const PointLight& pointLight) const;
	};


}