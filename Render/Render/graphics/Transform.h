#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace ginkgo{

	class Transform {
	private:
		glm::mat4 matrix;
	public:
		Transform()	: Transform(glm::mat4()){ }
		Transform(const glm::mat4& matrix) { this->matrix = matrix; }
		const glm::mat4& scaleMatrix(const glm::vec3& scale) { matrix = glm::scale(matrix, scale); return matrix; }
		const glm::mat4& translateMatrix(const glm::vec3& translation) { matrix = glm::translate(matrix, translation); return matrix; }
		const glm::mat4& rotateMatrix(float angleInRadians, const glm::vec3& rotation) { matrix = glm::rotate(matrix, angleInRadians, rotation); return matrix; }
		const glm::mat4& getMatrix() const { return matrix; }
		void setMatrix(const glm::mat4& matrix) { this->matrix = matrix; }
	};

}

/*
templated in the future for any kind of glm data type as needed
*/