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


	void Mesh::addData(std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices, std::vector<glm::vec2>& uvs, bool calculateNormals)
	{
		GLfloat* data;
		if (calculateNormals)
		{
			std::vector<glm::vec3> normals = calcNormals(vertices, indices);
			data = generateDataMatrixWithNormals(vertices, uvs, normals);
		}
		else
			data = generateDataMatrix(vertices, uvs);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, data_size * sizeof(GLfloat), data, GL_STATIC_DRAW); //&data[0]

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW); //TODO: indices //? too

		glBindVertexArray(0);

		delete data;
	}

	void Mesh::draw()
	{
		glBindVertexArray(VAO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data_size * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, data_size * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, data_size * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

	}

	GLfloat* Mesh::generateDataMatrix(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs)
	{
		data_size = vertices.size() * 5;
		GLfloat* data = new GLfloat[data_size];

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
	}

	GLfloat* Mesh::generateDataMatrixWithNormals(std::vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals)
	{
		data_size = vertices.size() * 8;
		GLfloat* data = new GLfloat[data_size];

		if (vertices.size() != uvs.size())
		{
			for (GLuint i = 0; i < vertices.size(); i++)
			{
				data[i * 8 + 0] = vertices[i].x;
				data[i * 8 + 1] = vertices[i].y;
				data[i * 8 + 2] = vertices[i].z;
				data[i * 8 + 3] = 0;
				data[i * 8 + 4] = 0;
				data[i * 8 + 5] = normals[i].x;
				data[i * 8 + 6] = normals[i].y;
				data[i * 8 + 7] = normals[i].z;
			}

		}
		else
		{
			for (GLuint i = 0; i < vertices.size(); i++)
			{
				data[i * 8 + 0] = vertices[i].x;
				data[i * 8 + 1] = vertices[i].y;
				data[i * 8 + 2] = vertices[i].z;
				data[i * 8 + 3] = uvs[i].x;
				data[i * 8 + 4] = uvs[i].y;
				data[i * 8 + 5] = normals[i].x;
				data[i * 8 + 6] = normals[i].y;
				data[i * 8 + 7] = normals[i].z;
			}
		}
		return data;
	}

	std::vector<glm::vec3>& Mesh::calcNormals(std::vector<glm::vec3>& vertices, std::vector<GLuint>& indices)
	{
		std::vector<glm::vec3> normals;

		for (int i = 0; i < indices.size(); i++)
		{
			int i0 = indices[i];
			int i1 = indices[i + 1];
			int i2 = indices[i + 2];

			glm::vec3 v1 = vertices[i1] - vertices[i0];
			glm::vec3 v2 = vertices[i2] - vertices[i0];

			glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

			normals[i0] = normals[i0] + normal;
			normals[i1] = normals[i1] + normal;
			normals[i2] = normals[i2] + normal;
		}
		
		for (int i = 0; i < vertices.size(); i++)
		{
			normals[i] = glm::normalize(normals[i]);
		}

		return normals;
	}

}