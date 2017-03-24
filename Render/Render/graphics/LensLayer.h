#pragma once

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>

#include "Transform.h"

namespace ginkgo {

	class Renderable;
	class LensShader;
	class Camera;
	class CubeMap;

	class LensLayer
	{
	private:
		std::vector<Renderable*> renderables;
		Transform model;
		std::vector<unsigned int> sizeTextureIDs;
	public:
		LensLayer(const std::vector<Renderable*>& renderables, const glm::mat4& model = glm::mat4());

		unsigned int getSize() const { return renderables.size(); }

		static bool compareRenderables(Renderable* r1, Renderable* r2);

		void addRenderable(Renderable* renderable);
		Renderable* alterRenderable(unsigned int index) const;
		const Renderable* getRenderable(unsigned int index) const;

		const glm::mat4& getModel() const;
		Transform& alterModel() { return model; };

		void draw(const glm::mat4& transformProjectionView, const glm::vec3& cameraPosition, const LensShader& phongShader, const CubeMap& cubeMap) const;
	};

}