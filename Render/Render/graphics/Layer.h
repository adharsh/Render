#pragma once

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>

namespace ginkgo {

	class Renderable;
	class PhongShader;
	class Camera;
	class Transform;
	class CubeMap;

	class Layer
	{
	private:
		std::vector<Renderable*> renderables;
		std::vector<unsigned int> sizeTextureIDs;
		Transform* model;
		static const unsigned int NO_TEXTURE = 0; //must be equal than 0 -> created textures will never have an id of 0

		static bool compareRenderables(Renderable* r1, Renderable* r2);
		static unsigned int determineTextureID(Renderable* r1);
	public:
		Layer(std::vector<Renderable*> renderables, const glm::mat4& model = glm::mat4());
		~Layer();

		unsigned int size() const { return renderables.size(); }

		void addRenderable(Renderable* renderable);
		Renderable* alterRenderable(unsigned int index) const;
		const Renderable* getRenderable(unsigned int index) const;
		
		const glm::mat4& getModel() const;
		Transform* alterModel() const { return model; };

		void draw(const glm::mat4& transformProjectionView, const glm::vec3& cameraPosition, const PhongShader& phongShader, const CubeMap& cubeMap) const;
	};

}