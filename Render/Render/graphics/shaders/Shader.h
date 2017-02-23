#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace ginkgo {

	class Shader
	{
	private:
		GLuint program;
		std::vector<GLuint> shaders;
	public:
		Shader();
		~Shader();

		void addVertexShader(const char* s);
		void addGeometryShader(const char* s);
		void addFragmentShader(const char* s);
		void addProgram(const char* s, GLenum type);
		void compileShader() const;

		GLuint load(const char* vertexShader, const char* fragShader) const;

		void setUniform1f(const GLchar* name, float value) const;
		void setUniform1fv(const GLchar* name, float* value, int count) const;
		void setUniform1i(const GLchar* name, int value) const;
		void setUniform1iv(const GLchar* name, int* value, int count) const;
		void setUniform2f(const GLchar* name, const glm::vec2& vector) const;
		void setUniform3f(const GLchar* name, const glm::vec3& vector) const;
		void setUniform4f(const GLchar* name, const glm::vec4& vector) const;
		void setUniformMat4(const GLchar* name, const glm::mat4& matrix) const;
		
		void bind() const;
		void unbind() const;
	private:
		GLint getUniformLocation(const GLchar* name) const;

	};


}
