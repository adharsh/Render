#pragma once

#include "LensMesh.h"

namespace ginkgo {

	LensMesh::LensMesh()
	{
		size = 0;
		data_size = 0;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	LensMesh::~LensMesh()
	{
		glDeleteBuffers(1, &EBO);
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void LensMesh::addData(const std::vector<glm::vec3>& positions, const std::vector<GLuint>& indices, const std::vector<glm::vec2>& uvs)
	{
		//Loading Data
		data_size = positions.size() * 5;
		GLfloat* data = new GLfloat[data_size];

		if (positions.size() != uvs.size())
			int a = 0; //take out once this assertion doesn't fail

		for (GLuint i = 0; i < positions.size(); i++)
		{
			data[i * 5 + 0] = positions[i].x;
			data[i * 5 + 1] = positions[i].y;
			data[i * 5 + 2] = positions[i].z;
			data[i * 5 + 3] = uvs[i].x;
			data[i * 5 + 4] = uvs[i].y;
		}

		//Binding Data
		size = indices.size();

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glBufferData(GL_ARRAY_BUFFER, data_size * sizeof(GLfloat), data, GL_STATIC_DRAW); //&data[0]
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW); //TODO: indices //? too

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		delete[] data;
	}

	void LensMesh::draw() const
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

}