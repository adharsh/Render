#pragma once

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Material.h"

namespace ginkgo {

	class Mesh;
	class Material;

	class Renderable
	{
	private:
		const Mesh* mesh;
		Material& material;
		glm::mat4 model;
	public:
		Renderable(const Mesh* mesh, Material& material, const glm::mat4& model);
		Renderable(const Mesh* mesh, Material& material);

		void setMesh(const Mesh* mesh) { this->mesh = mesh; }
		void setMaterial(const Material material) { this->material = material; }
		void setModel(const glm::mat4& model) { this->model = model; }
		Material& alterMaterial() { return material; }
		
		const Mesh& getMesh() const { return *mesh; }
		const Material& getMaterial() const { return material; }
		const glm::mat4& getModel() const { return model; }

		void draw() const;

		void scaleModel(const glm::vec3& scale) { model = glm::scale(model, scale); }
		void translateModel(const glm::vec3& translation) { model = glm::translate(model, translation); }
		void rotateModel(float angleInRadians, const glm::vec3& rotation) { model = glm::rotate(model, angleInRadians, rotation); }
	};

}

/*
Renderables all share a 
Mesh (pointer)
but each have a unique Material
but (possible) share the Material's const Texture

change to one Mesh changes all Rendrables
change to one Material changes one Rendrables
cannot change Material's const Texture

cannot change Material of a mesh?
*/