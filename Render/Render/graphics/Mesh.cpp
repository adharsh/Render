#pragma once

#include <gl\glew.h>
#include "Mesh.h"

namespace ginkgo {

	Mesh::Mesh()
	{
		size = 0;
		data_size = 0; 
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}
	
	
	void Mesh::addData(std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices, std::vector<glm::vec2>& uvs)
	{
		GLfloat* data = generateDataMatrix(vertices, uvs);
		
		size = indices.size();
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, data_size * sizeof(GLfloat), &data[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

		glBindVertexArray(0);
		
		delete data;
	}

	void Mesh::draw()
	{
		glBindVertexArray(VAO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	GLfloat* Mesh::generateDataMatrix(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs)
	{
		data_size = vertices.size() * 5;
		GLfloat* data = new GLfloat[data_size];
		//GLfloat data[data_size];

		if (vertices.size() != uvs.size())
		{
			for (GLuint i = 0; i < vertices.size(); i++)
			{
				data[i * 5 + 0] = vertices[i].x;
				data[i * 5 + 1] = vertices[i].y;
				data[i * 5 + 2] = vertices[i].z;
				data[i * 5 + 3] = 0;
				data[i * 5 + 4] = 0;
			}

		} 
		else
		{
			for (GLuint i = 0; i < vertices.size(); i++)
			{
				data[i * 5 + 0] = vertices[i].x;
				data[i * 5 + 1] = vertices[i].y;
				data[i * 5 + 2] = vertices[i].z;
				data[i * 5 + 3] = uvs[i].x;
				data[i * 5 + 4] = uvs[i].y;
			}
		}
		return data;
		//TODO: When do I delete data now?
	}

}
