#pragma once

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace ginkgo {

	class Renderable;
	class PhongShader;
	class Camera;

	class Layer
	{
	private:
		std::vector<Renderable*> renderables;
		std::vector<unsigned int> sizeTextureIDs;
		const PhongShader* shader;
		glm::mat4 model;
	
		static bool compareRenderables(Renderable* r1, Renderable* r2);
	public:
		Layer(std::vector<Renderable*> renderables, const PhongShader* shader, const Camera* camera);

		void addRenderable(Renderable* renderable);
		void draw(const glm::mat4& transformProjectionView, const glm::vec3& cameraPosition) const;

		Renderable* alterRenderable(unsigned int index) { if (index < 0 || index >= renderables.size()) return nullptr; return renderables[index]; }

		unsigned int getSize() const { return renderables.size(); }

		void scaleModel(const glm::vec3& scale) { model = glm::scale(model, scale); }
		void translateModel(const glm::vec3& translation) { model = glm::translate(model, translation); }
		void rotateModel(float angleInRadians, const glm::vec3& rotation) { model = glm::rotate(model, angleInRadians, rotation); }
	};

}