#pragma once

#include <gl\glew.h>
#include "Mesh.h"

namespace ginkgo {

	Mesh::Mesh()
	{
		size = 0;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	void Mesh::addVertices(std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices)
	{
		size = indices.size();
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	void Mesh::draw()
	{
		glBindVertexArray(VAO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

}
