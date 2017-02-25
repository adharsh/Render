#include "Layer.h"

#include "Camera.h"
#include "shaders/PhongShader.h"
#include "Renderable.h"
#include "Material.h"
#include "Texture.h"
#include "Transform.h"

namespace ginkgo {

	Layer::Layer(const std::vector<Renderable*> renderablesL, const PhongShader* shaderL, const glm::mat4& model)
		: renderables(renderablesL), shader(shaderL)
	{
		this->model = new Transform(model);

		std::sort(renderables.begin(), renderables.end(), compareRenderables);

		GLuint tid = 0;
		unsigned int size = 0;
		for (unsigned int c = 0; c < renderables.size(); c++)
		{
			tid = renderables[c]->getMaterial().getTexture().getID();
			size++;
			if ((c == renderables.size() - 1) || (renderables[c + 1]->getMaterial().getTexture().getID() != tid))
			{
				sizeTextureIDs.push_back(size);
				size = 0;
			}
		}

	}

	Layer::~Layer()
	{
		delete model;
	}

	bool Layer::compareRenderables(Renderable* r1, Renderable* r2)
	{
		return r1->getMaterial().getTexture().getID() < r2->getMaterial().getTexture().getID();
	}

	const glm::mat4& Layer::getModel() const 
	{
		return model->getMatrix(); 
	}

	void Layer::addRenderable(Renderable* renderable)
	{
		int left = 0;
		int right = renderables.size() - 1;

		int middle = 0;
		bool found = false;
		unsigned int value = renderable->getMaterial().getTexture().getID();

		while (left <= right)
		{
			middle = (left + right) / 2;
			unsigned int find = renderables[middle]->getMaterial().getTexture().getID();
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

	void Layer::draw(const glm::mat4& transformProjectionView, const glm::vec3& cameraPosition) const
	{
		shader->bind();

		unsigned int b = 0;
		for (unsigned int i = 0; i < sizeTextureIDs.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, renderables[b]->getMaterial().getTexture().getID());
			for (unsigned int a = 0; a < sizeTextureIDs[i]; a++)
			{
				shader->updateUniforms(
					renderables[b]->getModel(), 
					transformProjectionView * model->getMatrix() * renderables[b]->getModel(),
					renderables[b]->getMaterial(), 
					cameraPosition);
				renderables[b]->draw();
				b++;
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		shader->unbind();

	}

}