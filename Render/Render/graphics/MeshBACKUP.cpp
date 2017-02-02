#pragma once

#include <gl\glew.h>
#include "Mesh.h"

namespace ginkgo {

		Mesh::Mesh()
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);
		}

		void Mesh::addVertices(std::vector<glm::vec3>& vertices)
		{
		
			size = vertices.size();
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_DYNAMIC_DRAW);
		}

		void Mesh::draw()
		{
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
			glDrawArrays(GL_TRIANGLES, 0, size);

			glDisableVertexAttribArray(0);
		}



	}
