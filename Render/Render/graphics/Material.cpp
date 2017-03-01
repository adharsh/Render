#include "Material.h"

#include "Texture.h"

namespace ginkgo {

	const float Material::REFLECT = 0.0f;
	const float Material::NO_ENVIRONMENTAL_MAPPING = -1.0f;

	Material::Material(float refractiveIndex)
		: Material(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2, 32, refractiveIndex, 1.0f, nullptr)
	{ }

	Material::Material(const Texture* texture)
		: Material(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2, 32, Material::NO_ENVIRONMENTAL_MAPPING, 1.0f, texture)
	{ }

	Material::Material(const glm::vec4& color, const Texture* texture)
		: Material(color, 2, 32, Material::NO_ENVIRONMENTAL_MAPPING, 1.0f, texture)
	{ }

	Material::Material(float refractiveIndex, const Texture* texture)
		: Material(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2, 32, refractiveIndex, 1.0f, texture)
	{ }

	Material::Material(float refractiveIndex, float rIntensity, const Texture* texture)
		: Material(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2, 32, refractiveIndex, rIntensity, texture)
	{}

	Material::Material(const glm::vec4& color, float specularIntensity, float specularExponent, float refractiveIndex, float rIntensity, const Texture* texture)
		: color(color), specularIntensity(specularIntensity), specularPower(specularExponent), refractiveIndex(refractiveIndex), rIntensity(rIntensity), texture(texture)
	{ }

}
