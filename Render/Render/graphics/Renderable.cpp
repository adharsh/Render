#pragma once

#include "Renderable.h"

#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

namespace ginkgo {
	
	Renderable::Renderable(const Mesh* mesh, Material* material, const glm::mat4& model)
		: mesh(mesh), material(material)
	{
		this->model = new Transform(model);
	}

	Renderable::~Renderable()
	{
		delete model;
	}
	
	const glm::mat4& Renderable::getModel() const 
	{ 
		return model->getMatrix(); 
	}


	void Renderable::draw() const
	{
		mesh->draw(); 
	}

}
