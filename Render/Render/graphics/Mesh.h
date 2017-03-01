#pragma once

#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>

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
		~Mesh();
		void addData(const std::vector<glm::vec3>& positions, const std::vector<GLuint>& indices, const std::vector<glm::vec2>& uvs, bool haveNormals = true);
		void addDataLOL();
		void draw() const;
		void drawLOL() const;
	};


}
