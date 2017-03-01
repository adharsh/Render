#pragma once

#include <map>
#include <string>

#include <glm/glm.hpp>

#include "Shader.h"
#include "../Transform.h"

namespace ginkgo {
	
	class Transform;

	class CubeMap : public Shader
	{
	private:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int textureID;
		Transform* model;
	public:
		static const unsigned int RIGHT = 0;
		static const unsigned int LEFT = 1;
		static const unsigned int TOP = 2;
		static const unsigned int BOTTOM = 3;
		static const unsigned int FRONT = 4;
		static const unsigned int BACK = 5;
	public:
		CubeMap(std::map<unsigned int, const char*> faces, float scale, const glm::mat4& model = glm::mat4());
		~CubeMap();
		void draw(const glm::mat4& transformProjectionView) const;
		const glm::mat4& getModel() const;
		Transform* alterModel() const { return model; }
		void bindCubeMapTexture(int textureNumber) const;
		void unbindCubeMapTexture() const;
	};
	
}