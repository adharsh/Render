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
		GLuint data_size;
	public:
		Mesh();
		void addData(std::vector<glm::vec3>& positions, std::vector<GLuint>& indices, std::vector<glm::vec2>& uvs, bool haveNormals = true);
		void draw();
	private:
		GLfloat* generateDataMatrix(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals);
	};


}
