#include "LensLayer.h"

#include "Camera.h"
#include "shaders/LensShader.h"
#include "Renderable.h"
#include "Material.h"
#include "Texture.h"
#include "Transform.h"
#include "shaders/CubeMap.h"

#include "../cuda/Lensing.cuh"

namespace ginkgo {

	LensLayer::LensLayer(const std::vector<Renderable*>& renderablesL, const glm::mat4& model)
		: renderables(renderablesL), model(model)
	{
		std::sort(renderables.begin(), renderables.end(), compareRenderables);

		GLuint tid = 0;
		unsigned int size = 0;
		for (unsigned int c = 0; c < renderables.size(); c++)
		{
			tid = renderables[c]->getMaterial().getTexture()->getID();
			size++;
			if ((c == renderables.size() - 1) || ((renderables[c + 1]->getMaterial().getTexture()->getID()) != tid))
			{
				sizeTextureIDs.emplace_back(size);
				size = 0;
			}
		}

	}

	bool LensLayer::compareRenderables(Renderable* r1, Renderable* r2)
	{
		return r1->getMaterial().getTexture()->getID() < r2->getMaterial().getTexture()->getID();
	}


	Renderable* LensLayer::alterRenderable(unsigned int index) const
	{
		if (index < 0 || index >= renderables.size())
			return nullptr;

		for (unsigned int i = 0; i < renderables.size(); i++)
			if (renderables[i]->getIndex() == index)
				return renderables[i];

		return nullptr;
	}

	const Renderable* LensLayer::getRenderable(unsigned int index) const
	{
		if (index < 0 || index >= renderables.size())
			return nullptr;

		for (unsigned int i = 0; i < renderables.size(); i++)
			if (renderables[i]->getIndex() == index)
				return renderables[i];

		return nullptr;
	}

	const glm::mat4& LensLayer::getModel() const
	{
		return model.getMatrix();
	}

	void LensLayer::addRenderable(Renderable* renderable)
	{
		int left = 0;
		int right = renderables.size() - 1;

		int middle = 0;
		bool found = false;
		unsigned int value = renderable->getMaterial().getTexture()->getID();

		while (left <= right)
		{
			middle = (left + right) / 2;
			unsigned int find = renderables[middle]->getMaterial().getTexture()->getID();
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
			renderables.emplace_back(renderable);
			sizeTextureIDs.emplace_back(1);
		}
	}

	void LensLayer::draw(const glm::mat4& transformProjectionView, const glm::vec3& cameraPosition, const LensShader& lensShader, const CubeMap& cubeMap) const
	{
		lensShader.bind();

		std::vector<std::vector<glm::dvec4>> normals;
		#define n 510
		for (int r = 0; r < n; r++)
		{
		normals.emplace_back(std::vector<glm::dvec4>());
		for (int c = 0; c < n; c++)
		{
		normals[r].emplace_back(glm::dvec4(0.0f, 0.0f, 1.0f, 1.0f));
		}
		}
		lensShader.updateNormals(normals);
		

		//lensShader.updateNormals(lensing());

		unsigned int b = 0;

		lensShader.setUniform1i("skybox", 0);		   //dependant on lensFragment.fs
		lensShader.setUniform1i("normalMap", 1); //dependant on lensFragment.fs
		glActiveTexture(GL_TEXTURE0); cubeMap.bindCubeMapTexture();
		for (unsigned int i = 0; i < sizeTextureIDs.size(); i++)
		{
			glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, renderables[b]->getMaterial().getTexture()->getID());
			for (unsigned int a = 0; a < sizeTextureIDs[i]; a++)
			{
				lensShader.updateUniforms(
					model.getMatrix() * renderables[b]->getModel(),
					transformProjectionView * model.getMatrix() * renderables[b]->getModel(),
					cameraPosition);
				renderables[b]->draw();
				b++;
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		cubeMap.unbindCubeMapTexture();

		lensShader.unbind();
	}

}
