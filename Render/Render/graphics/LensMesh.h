#pragma once

#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>

#include "Mesh.h"

namespace ginkgo {

	class LensMesh : public Mesh
	{
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		GLuint size;
		GLuint data_size;
	public:
		LensMesh();
		~LensMesh();
		void addData(const std::vector<glm::vec3>& positions, const std::vector<GLuint>& indices, const std::vector<glm::vec2>& uvs);
		void draw() const;
	};


}
