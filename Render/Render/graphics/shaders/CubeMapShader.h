#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "Shader.h"
#include "../Transform.h"

namespace ginkgo {
	
	class Transform;

	class CubeMapShader : public Shader
	{
	private:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int textureID;
		Transform* model;
	public:
		CubeMapShader(std::vector<const char*> faces, float scale, const glm::mat4& = glm::mat4());
		~CubeMapShader();
		void draw(const glm::mat4& transformProjectionView) const;
		const glm::mat4& getModel() const;
		Transform* alterModel() const { return model; }
	};


}

/*
vector of images must be in following order:
right.jpg
left.jpg
top.jpg
bottom.jpg
back.jpg
front.jpg
*/