#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace ginkgo {

	class Transform
	{
	private:
		glm::mat4 matrix;
	public:
		Transform() : Transform(glm::mat4()) { }
		Transform(const glm::mat4& matrix) { this->matrix = matrix; }
		const glm::mat4& getMatrix() const { return matrix; }
		void setMatrix(const glm::mat4& matrix) { this->matrix = matrix; }
		
		Transform* scaleMatrix(const glm::vec3& scale) { matrix = glm::scale(matrix, scale); return this; }
		Transform* translateMatrix(const glm::vec3& translation) { matrix = glm::translate(matrix, translation); return this; }
		Transform* rotateMatrix(float angleInRadians, const glm::vec3& rotation) { matrix = glm::rotate(matrix, angleInRadians, rotation); return this; }
				 
		Transform* newScaleMatrix(const glm::vec3& scale) { matrix = glm::scale(glm::mat4(), scale); return this; }
		Transform* newTranslateMatrix(const glm::vec3& translation) { matrix = glm::translate(glm::mat4(), translation); return this; }
		Transform* newRotateMatrix(float angleInRadians, const glm::vec3& rotation) { matrix = glm::rotate(glm::mat4(), angleInRadians, rotation); return this; }
	};

}

/*
capability for chaining
templated in the future for any kind of glm data type as needed
*/