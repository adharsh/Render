#include "Material.h"

#include "Texture.h"

namespace ginkgo {

	Material::Material(const glm::vec4& color, const Texture* texture)
		: Material(color, 2, 32, texture)
	{ }

	Material::Material(const glm::vec4& color, float specularIntensity, float specularExponent, const Texture* texture)
		: color(color), specularIntensity(specularIntensity), specularPower(specularExponent), texture(texture)
	{ }

}
