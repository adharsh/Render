#include <algorithm>
#include <vector>

#include "Layer.h"


namespace ginkgo {

	Layer::Layer(const std::vector<Renderable*> renderablesL, PhongShader* shaderL, Camera* cameraL)
		: renderables(renderablesL), shader(shaderL), camera(cameraL)
	{
		std::sort(renderables.begin(), renderables.end(), compareRenderables);

		GLuint tid = 0;
		unsigned int size = 0;
		for (unsigned int c = 0; c < renderables.size(); c++)
		{
			tid = renderables[c]->alterTexture().getID();
			size++;
			if ((c == renderables.size() - 1) || (renderables[c + 1]->alterTexture().getID() != tid))
			{
				sizeTextureIDs.push_back(size);
				size = 0;
			}
		}

	}

	bool Layer::compareRenderables(Renderable* r1, Renderable* r2)
	{
		return r1->alterTexture().getID() < r2->alterTexture().getID();
	}

	void Layer::addRenderable(Renderable* renderable)
	{
		int left = 0;
		int right = renderables.size() - 1;

		int middle = 0;
		bool found = false;
		unsigned int value = renderable->alterTexture().getID();

		while (left <= right)
		{
			middle = (left + right) / 2;
			unsigned int find = renderables[middle]->alterTexture().getID();
			if (find == value)
			{
				found = true;
				break;
			}
			else if (find > value)
				right = middle - 1;
			else
				left = middle + 1;
		}
		if (found)
		{
			renderables.insert(renderables.begin() + middle, renderable);
			int sum = 0;
			for (int i = 0; i < sizeTextureIDs.size(); i++)
			{
				sum += sizeTextureIDs[i];
				if (sum > middle)
				{
					sizeTextureIDs[i]++;
					break;
				}
			}
		}
		else
		{
			renderables.push_back(renderable);
			sizeTextureIDs.push_back(1);
		}
	}

	void Layer::draw() const
	{
		shader->bind();

		unsigned int b = 0;
		for (unsigned int i = 0; i < sizeTextureIDs.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, renderables[b]->alterTexture().getID());
			for (int a = 0; a < sizeTextureIDs[i]; a++)
			{
				shader->updateUniforms(renderables[b]->getModel(), camera->getProjection() * camera->getView() * model * renderables[b]->getModel(), renderables[b]->alterTexture(), camera->getCameraPosition());
				renderables[b]->draw();
				b++;
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		shader->unbind();

	}

}