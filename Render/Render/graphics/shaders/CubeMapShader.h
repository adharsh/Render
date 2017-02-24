#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "Shader.h"

namespace ginkgo {
	

	class CubeMapShader : public Shader
	{
	private:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int textureID;

	public:
		CubeMapShader(std::vector<const char*> faces, float scale);
		~CubeMapShader();
		void draw(const glm::mat4& transformProjectionView) const;

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