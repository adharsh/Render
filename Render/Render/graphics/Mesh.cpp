#pragma once

#include <gl\glew.h>
#include "Mesh.h"
#include <iostream>

namespace ginkgo {

	Mesh::Mesh()
	{
		size = 0;
		data_size = 0;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}


	void Mesh::addData(std::vector<glm::vec3>& positions, std::vector<GLuint>& indices, std::vector<glm::vec2>& uvs, bool haveNormals)
	{
		//Generating Normals
		std::vector<glm::vec3> normals;
		for (int i = 0; i < positions.size(); i++)
			normals.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

		if (haveNormals)
		{
			for (int i = 0; i < indices.size(); i += 3)
			{
				int i0 = indices[i];
				int i1 = indices[i + 1];
				int i2 = indices[i + 2];

				glm::vec3 v1 = positions[i1] - positions[i0];
				glm::vec3 v2 = positions[i2] - positions[i0];

				glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

				normals[i0] = normals[i0] + normal;
				normals[i1] = normals[i1] + normal;
				normals[i2] = normals[i2] + normal;
			}

			for (int i = 0; i < positions.size(); i++)
				normals[i] = glm::normalize(normals[i]);
		}

		//Loading Data
		GLfloat* data = generateDataMatrix(positions, uvs, normals);

		for (int i = 0; i < positions.size(); i++)
		{
			std::cout << data[i * 8 + 0] << std::endl;
			std::cout << data[i * 8 + 1] << std::endl;
			std::cout << data[i * 8 + 2] << std::endl;
			std::cout << data[i * 8 + 3] << std::endl;
			std::cout << data[i * 8 + 4] << std::endl;
			std::cout << data[i * 8 + 5] << std::endl;
			std::cout << data[i * 8 + 6] << std::endl;
			std::cout << data[i * 8 + 7] << std::endl << std::endl;
		}

		size = indices.size();

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, data_size * sizeof(GLfloat), data, GL_STATIC_DRAW); //&data[0]

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW); //TODO: indices //? too

		glBindVertexArray(0);

		//delete data;
	}

	void Mesh::draw()
	{
		glBindVertexArray(VAO);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));

		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	GLfloat* Mesh::generateDataMatrix(std::vector<glm::vec3>& positions, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& normals)
	{
		data_size = positions.size() * 8;
		GLfloat* data = new GLfloat[data_size];

	/*	if (positions.size() != uvs.size() || positions.size() != normals.size())
		{
			std::cout << "Incorrect amount of data. Should be the same number of sets of positions, uvs, and normals." << std::endl;
			system("pause");
			return NULL;
		}*/
	

		for (GLuint i = 0; i < positions.size(); i++)
		{
			data[i * 8 + 0] = positions[i].x;
			data[i * 8 + 1] = positions[i].y;
			data[i * 8 + 2] = positions[i].z;
			data[i * 8 + 3] = uvs[i].x;
			data[i * 8 + 4] = uvs[i].y;
			data[i * 8 + 5] = normals[i].x;
			data[i * 8 + 6] = normals[i].y;
			data[i * 8 + 7] = normals[i].z;
		}

		return data;
	}

}