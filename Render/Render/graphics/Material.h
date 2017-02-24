#pragma once

#include <glm/glm.hpp>

namespace ginkgo {

	class Texture;

	class Material
	{
	private:
		const Texture* texture;
		glm::vec4 color;
		float specularIntensity;
		float specularPower;
	public:
		Material(const glm::vec4& color, const Texture* texture);
		Material(const glm::vec4& color, float specularIntensity, float specularExponent, const Texture* texture);
		
		const Texture& getTexture() const { return *texture; }
		const glm::vec4& getColor() const { return color; }
		const float getSpecularIntensity() const { return specularIntensity; }
		const float getSpecularPower() const { return specularPower; }

		void setColor(const glm::vec4& color) { this->color = color; }

		const void setSpecularIntensity(float specular_Intensity) { specularIntensity = specular_Intensity; }
		const void setSpecularPower(float specular_Power) { this->specularPower = specular_Power; }

	};

}
