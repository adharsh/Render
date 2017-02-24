#pragma once

#include "Renderable.h"

#include "Mesh.h"
#include "Material.h"

namespace ginkgo {
	
	Renderable::Renderable(const Mesh* mesh, Material& material, const glm::mat4& model)
		: mesh(mesh), material(material), model(model)
	{ }

	Renderable::Renderable(const Mesh* mesh, Material& material)
		: Renderable(mesh, material, glm::mat4() )
	{ }

	void Renderable::draw() const
	{
		mesh->draw(); 
	}
}
