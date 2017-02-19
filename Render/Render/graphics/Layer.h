#pragma once

#include "Renderable.h"
#include "Camera.h"
#include "shaders\PhongShader.h"

namespace ginkgo {

	class Layer
	{
	private:
		std::vector<Renderable*> renderables;
		std::vector<GLuint> sizeTextureIDs;
		const PhongShader* shader;
		const Camera* camera;
		glm::mat4 model;
	
		static bool compareRenderables(Renderable* r1, Renderable* r2);
	public:
		Layer(std::vector<Renderable*> renderables, PhongShader* shader, Camera* camera);

		void addRenderable(Renderable* renderable);
		void draw() const;

		Renderable* alterRenderable(unsigned int index) { return renderables[index]; }
		unsigned int getSize() const { return renderables.size(); }

		void scaleModel(const glm::vec3& scale) { model = glm::scale(model, scale); }
		void translateModel(const glm::vec3& translation) { model = glm::translate(model, translation); }
		void rotateModel(float angleInRadians, const glm::vec3& rotation) { model = glm::rotate(model, angleInRadians, rotation); }
	};

}