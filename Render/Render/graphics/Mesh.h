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
		void addData(std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices, std::vector<glm::vec2>& uvs);
		void draw();
	private:
		GLfloat* generateDataMatrix(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs);
		GLfloat* generateDataMatrixWithNormals(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals);
	};


}
