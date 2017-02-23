#pragma once

#include <gl/glew.h>
#include <glm/gtc/matrix_transform.hpp>

namespace ginkgo {

	class Mesh;
	class Texture;

	class Renderable
	{
	private:
		const Mesh* mesh;
		const Texture* texture;
		glm::mat4 model;
	public:
		Renderable(const Mesh* mesh, const Texture* texture, const glm::mat4& model);
		Renderable(const Mesh* mesh, const Texture* texture);

		void setMesh(const Mesh* mesh) { this->mesh = mesh; }
		void setTexture(const Texture* texture) { this->texture = texture; }
		void setModel(const glm::mat4& model) { this->model = model; }

		const Mesh& getMesh() const { return *mesh; }
		const Texture& alterTexture() { return *texture; }
		const glm::mat4& getModel() const { return model; }

		void draw() const;

		void scaleModel(const glm::vec3& scale) { model = glm::scale(model, scale); }
		void translateModel(const glm::vec3& translation) { model = glm::translate(model, translation); }
		void rotateModel(float angleInRadians, const glm::vec3& rotation) { model = glm::rotate(model, angleInRadians, rotation); }
	};

}