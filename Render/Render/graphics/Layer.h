#pragma once

#include "Renderable.h"
#include "Camera.h"
#include "shaders\PhongShader.h"

namespace ginkgo {

	class Layer
	{
	private:
		std::vector<Renderable*> renderables;
		std::vector<GLuint> textureIDs;
		std::vector<GLuint> sizeTextureIDs;
		const PhongShader* shader;
		const Camera* camera;

		static bool compareRenderables(Renderable* r1, Renderable* r2);

	public:
		Layer(std::vector<Renderable*> renderables, PhongShader* shader, Camera* camera);

		void addRenderable(Renderable* renderable);
		void draw() const;

		Renderable* alterRenderable(unsigned int index) { return renderables[index]; }
		unsigned int getSize() const { return renderables.size(); }

	};

}