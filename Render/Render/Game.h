#pragma once

#include <iostream>
#include <cmath>

#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Time.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "utils/ObjLoader.h"

namespace ginkgo {

	class Game
	{
	private:
		Window& window;
		Shader shader;
		Mesh mesh;
		Texture texture;

		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 model;
		glm::mat4 transform;
	public:
		Game(Window& a) : window(a), texture()
		{
			shader.addVertexShader("Render/res/shaders/basicVertex.vs");
			shader.addFragmentShader("Render/res/shaders/basicFragment.fs");
			shader.compileShader();

			projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 100.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
#if 1
			
			ObjIntermediate obj;
			obj.LoadObj("Render/res/models/monkey.obj");

			std::vector<glm::vec3> vertices = obj.getVertexList();
			std::vector<GLuint> indices = obj.getIndexList();
			
			for (unsigned int i = 0; i < vertices.size(); i++)
				std::cout << vertices[i].x << ",  " << vertices[i].y << ",  " << vertices[i].z << ",  " << std::endl;
			
			for (unsigned int i = 0; i < indices.size(); i++)
				indices[i]--;

			for (unsigned int i = 0; i < indices.size(); i += 3)
				std::cout << indices[i] << ", " << indices[i+1] << ", " << indices[i+2] << std::endl;
			
			mesh.addVertices(vertices, indices);
#else

			std::vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(-1, -1, 0));
			vertices.push_back(glm::vec3(-1, 1, 0));
			vertices.push_back(glm::vec3(1, 1, 0));
			vertices.push_back(glm::vec3(1, -1, 0));

			std::vector<GLuint> indices;
			indices.push_back(0); indices.push_back(1); indices.push_back(3);
			indices.push_back(1); indices.push_back(3); indices.push_back(2);
			indices.push_back(3); indices.push_back(2); indices.push_back(0);
			indices.push_back(2); indices.push_back(0); indices.push_back(1);

			mesh.addVertices(vertices, indices);
#endif

		}

		void input()
		{
			if (window.isKeyPressed(GLFW_KEY_UP))
				std::cout << "Pressed Up\n";

		}

		float temp = 0.0f;
		void update()
		{
			temp += Time::getDelta();
			float a = sin(temp*1.5)*0.001f;
			//transform = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 1000.f);
			//transform = glm::translate(glm::vec3(a, 0, -2));
			//transform = glm::scale(transform, glm::vec3(0.9f, 0.9f, 0.9f));
			model = glm::rotate(model, a, glm::vec3(1.0f, 0.0f, 0.0f));
		}

		void render()
		{
			shader.bind();
			transform = projection * view * model;
			shader.setUniformMat4("transform", transform);
			mesh.draw();
			//texture.draw();
			shader.unbind();
		}

	};


}
