#pragma once

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>

namespace ginkgo {

	class Renderable;
	class PhongShader;
	class Camera;
	class Transform;

	class Layer
	{
	private:
		std::vector<Renderable*> renderables;
		std::vector<unsigned int> sizeTextureIDs;
		const PhongShader* shader;
		Transform* model;
	
		static bool compareRenderables(Renderable* r1, Renderable* r2);
	public:
		Layer(std::vector<Renderable*> renderables, const PhongShader* shader, const glm::mat4& model = glm::mat4());
		~Layer();

		unsigned int getSize() const { return renderables.size(); }

		void addRenderable(Renderable* renderable);
		Renderable* alterRenderable(unsigned int index) const { if (index < 0 || index >= renderables.size()) return nullptr; return renderables[index]; }
		const Renderable* getRenderable(unsigned int index) { if (index < 0 || index >= renderables.size()) return nullptr; return renderables[index]; }
		
		const glm::mat4& getModel() const;
		Transform* alterModel() const { return model; };

		void draw(const glm::mat4& transformProjectionView, const glm::vec3& cameraPosition) const;

	};

}