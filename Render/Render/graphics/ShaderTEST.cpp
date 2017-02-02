#include "Shader.h"
#include "../utils/FileUtils.h"


namespace ginkgo {

	Shader::Shader()
	{
		program = glCreateProgram();
		std::cout << "Constructor" << std::endl;
		system("PAUSE");
	}

	Shader::~Shader()
	{
		glDeleteProgram(program);
	}

	void Shader::addVertexShader(const char* file)
	{
		addProgram(file, GL_VERTEX_SHADER);
	}

	void Shader::addGeometryShader(const char* file)
	{
		addProgram(file, GL_GEOMETRY_SHADER);
	}

	void Shader::addFragmentShader(const char* file)
	{
		addProgram(file, GL_FRAGMENT_SHADER);
	}

	void Shader::addProgram(const char* file, GLenum type)
	{
		GLuint shaderID = glCreateShader(type);
		std::string shaderSourceString = FileUtils::read_file(file);
		const char*  shaderSource = shaderSourceString.c_str();

		glShaderSource(shaderID, 1, &shaderSource, NULL);
		glCompileShader(shaderID);

		glAttachShader(program, shaderID);
	}

	void Shader::compileShader()
	{
		glLinkProgram(program);
		glValidateProgram(program);
	}


	GLuint Shader::load(const char* vertexShader, const char* fragShader)
	{
		std::cout << "Shader::load()" << std::endl;
		system("PAUSE");

		//*********Vertex Shader
		GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
		std::string vertSourceString = FileUtils::read_file(vertexShader);
		const char* vertSource = vertSourceString.c_str();
		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		//*********Fragment Shader
		GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fragSourceString = FileUtils::read_file(fragShader);
		const char* fragSource = fragSourceString.c_str();
		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		glAttachShader(this->program, vertex);
		glAttachShader(this->program, fragment);

		glLinkProgram(this->program);
		glValidateProgram(this->program);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		return this->program;
	}



	void Shader::bind() const
	{
		glUseProgram(program);
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	GLint Shader::getUniformLocation(const GLchar* name)
	{
		return glGetUniformLocation(program, name);
	}

	void Shader::setUniform1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform1fv(const GLchar* name, float* value, int count)
	{
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1iv(const GLchar* name, int* value, int count)
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void Shader::setUniform1i(const GLchar* name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}
	void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector)
	{
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

}
