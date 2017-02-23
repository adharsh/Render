#pragma once

#include "Renderable.h"

#include "Mesh.h"
#include "Texture.h"

namespace ginkgo {
	
	
	Renderable::Renderable(const Mesh* mesh, const Texture* texture, const glm::mat4& model)
		: mesh(mesh), texture(texture), model(model)
	{ }


	Renderable::Renderable(const Mesh* mesh, const Texture* texture)
		: Renderable(mesh, texture, glm::mat4())
	{ }
	
	void Renderable::draw() const 
	{
		mesh->draw(); 
	}
}
