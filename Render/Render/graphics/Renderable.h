#pragma once

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "Texture.h"

namespace ginkgo {

	class Renderable
	{
	private:
		const Mesh* mesh;
		Texture texture;
		glm::mat4 model;
	public:
		Renderable(const Mesh* mesh, Texture& texture, const glm::mat4& model)
			: mesh(mesh), texture(texture), model(model)
		{ }

		Renderable(const Mesh* mesh, Texture& texture)
			: Renderable(mesh, texture, glm::mat4())
		{ }

		void setMesh(const Mesh* mesh) { this->mesh = mesh; }
		void setTexture(Texture& texture) { this->texture = texture; }
		void setModel(const glm::mat4& model) { this->model = model; }

		const Mesh* getMesh() const { return mesh; }
		Texture& alterTexture() { return texture; }
		const glm::mat4& getModel() const { return model; }

		void draw() const { mesh->draw(); }

		void scaleModel(const glm::vec3& scale) { model = glm::scale(model, scale); }
		void translateModel(const glm::vec3& translation) { model = glm::translate(model, translation); }
		void rotateModel(float angleInRadians, const glm::vec3& rotation) { model = glm::rotate(model, angleInRadians, rotation); }
	};

}