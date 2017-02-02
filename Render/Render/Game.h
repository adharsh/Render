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
#include "graphics/BasicShader.h"
#include "utils/ObjLoader.h"

namespace ginkgo {

	class Game
	{
	private:
		Window& window;
		BasicShader shader;
		Mesh mesh;
		Texture texture;

		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 model;
		glm::mat4 transform;
	public:
		Game(Window& a) : window(a)
		{
			projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 100.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
#if 0
			
			ObjIntermediate obj;
			obj.LoadObj("Render/res/models/cube.obj");

			std::vector<glm::vec3> vertices = obj.getVertexList();
			std::vector<GLuint> indices = obj.getIndexList();
			std::vector<glm::vec2> uvs = obj.getUVList();
			
			for (unsigned int i = 0; i < uvs.size(); i++)
				std::cout << uvs[i].x << ",  " << uvs[i].y << std::endl;

			/*for (unsigned int i = 0; i < vertices.size(); i++)
				std::cout << vertices[i].x << ",  " << vertices[i].y << ",  " << vertices[i].z << ",  " << std::endl;
			
			for (unsigned int i = 0; i < indices.size(); i += 3)
				std::cout << indices[i] << ", " << indices[i+1] << ", " << indices[i+2] << std::endl;*/
			
			mesh.addData(vertices, indices, uvs);
#else

			texture = Texture("Render/res/textures/Hi.png", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			//texture = Texture("", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

			std::vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(-1, -1, 0));
			vertices.push_back(glm::vec3(-1, 1, 0));
			vertices.push_back(glm::vec3(1, 1, 0));
			vertices.push_back(glm::vec3(1, -1, 0));

			std::vector<glm::vec2> uvs;
			uvs.push_back(glm::vec2(0.0f, 0.0f));
			uvs.push_back(glm::vec2(0.5f, 0.0f));
			uvs.push_back(glm::vec2(1.0f, 0.0f));
			uvs.push_back(glm::vec2(0.0f, 0.5f));

			std::vector<GLuint> indices;
			indices.push_back(0); indices.push_back(1); indices.push_back(3);
			indices.push_back(1); indices.push_back(3); indices.push_back(2);
			indices.push_back(3); indices.push_back(2); indices.push_back(0);
			indices.push_back(2); indices.push_back(0); indices.push_back(1);

			mesh.addData(vertices, indices, uvs);
#endif
		}

		void input()
		{
			if (window.isKeyPressed(GLFW_KEY_UP))
				std::cout << "Pressed Up\n";

			if (window.isKeyPressed(GLFW_KEY_DOWN))
				std::cout << "Pressed Down\n";
			
			if (window.isKeyPressed(GLFW_KEY_RIGHT))
				std::cout << "Pressed Right\n";

			if (window.isKeyPressed(GLFW_KEY_LEFT))
				std::cout << "Pressed Left\n";



		}

		float temp = 0.0f;
		void update()
		{
			temp += Time::getDelta();
			float a = sin(temp*1.5)*0.001f;
			texture.setColor(glm::vec4(sin(temp), -sin(temp), sin(temp), 1.0f));
			model = glm::rotate(model, a, glm::vec3(1.0f, 0.0f, 0.0f));
			window.setClearColor(glm::vec4(sin(temp), sin(temp), sin(temp), sin(temp)));
		}

		void render()
		{
			shader.bind();
			shader.updateUniforms(projection * view * model, texture);
			mesh.draw();
			shader.unbind();
		}

	};


}
