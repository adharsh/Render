#pragma once

#include <vector>
#include <gl\glew.h>
#include <glm\glm.hpp>

namespace ginkgo {

	class Mesh
	{
	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		GLuint size;

	public:
		Mesh();
		void addVertices(std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices);
		void draw();
	};


}
