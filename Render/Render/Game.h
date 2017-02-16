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
#include "graphics/PhongShader.h"
#include "utils/ObjLoader.h"
#include "graphics\Camera.h"

namespace ginkgo {

	class Game
	{
	private:
		Window& window;
		PhongShader shader;
		Mesh mesh;
		Mesh mesh2;
		Texture* texture;

		Camera* camera;
		
	public:
		Game(Window& win) : window(win)
		{

#if 0
			//No UVS generated from this, why?
			ObjIntermediate obj;
			obj.LoadObj("Render/res/models/cube.obj");

			std::vector<glm::vec3> vertices = obj.getVertexList();
			std::vector<GLuint> indices = obj.getIndexList();
			std::vector<glm::vec2> uvs = obj.getUVList();

			/*for (unsigned int i = 0; i < uvs.size(); i++)
			std::cout << uvs[i].x << ",  " << uvs[i].y << std::endl; */

			/*for (unsigned int i = 0; i < vertices.size(); i++)
			std::cout << vertices[i].x << ",  " << vertices[i].y << ",  " << vertices[i].z << ",  " << std::endl;

			for (unsigned int i = 0; i < indices.size(); i += 3)
			std::cout << indices[i] << ", " << indices[i+1] << ", " << indices[i+2] << std::endl;*/

			mesh.addData(vertices, indices, uvs, false);
#endif

#if 0
			//ERROR when creating a plane
			std::vector<glm::vec3> positions;
			positions.push_back(glm::vec3(-1, -1, 0));
			positions.push_back(glm::vec3(-1, 1, 0));
			positions.push_back(glm::vec3(1, 1, 0));
			positions.push_back(glm::vec3(1, -1, 0));

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

#elif 0
			std::vector<glm::vec3> positions;
			positions.push_back(glm::vec3(-1.0f, -1.0f, 0.5773f));
			positions.push_back(glm::vec3(0.0f, -1.0f, -1.15475f));
			positions.push_back(glm::vec3(1.0f, -1.0f, 0.5773f));
			positions.push_back(glm::vec3(0.0f, 1.0f, 0.0f));

			std::vector<glm::vec2> uvs;
			uvs.push_back(glm::vec2(0.0f, 0.0f));
			uvs.push_back(glm::vec2(0.5f, 0.0f));
			uvs.push_back(glm::vec2(1.0f, 0.0f));
			uvs.push_back(glm::vec2(0.0f, 0.5f));

			std::vector<GLuint> indices;
			indices.push_back(0); indices.push_back(3); indices.push_back(1);
			indices.push_back(1); indices.push_back(3); indices.push_back(2);
			indices.push_back(2); indices.push_back(3); indices.push_back(0);
			indices.push_back(1); indices.push_back(2); indices.push_back(0);

			mesh.addData(positions, indices, uvs, true);
#elif 1
			//window.disableMouseCursor();
			float fieldDepth = 1.0f;
			float fieldWidth = 1.0f;

			std::vector<glm::vec3> positions;
			std::vector<glm::vec2> uvs;
			std::vector<GLuint> indices;

			positions.push_back(glm::vec3(-fieldWidth, 0.0f, -fieldDepth));
			positions.push_back(glm::vec3(-fieldWidth, 0.0f, fieldDepth * 3));
			positions.push_back(glm::vec3(fieldWidth * 3, 0.0f, -fieldDepth));
			positions.push_back(glm::vec3(fieldWidth * 3, 0.0f, fieldDepth * 3));

			uvs.push_back(glm::vec2(0.0f, 0.0f));
			uvs.push_back(glm::vec2(0.0f, 1.0f));
			uvs.push_back(glm::vec2(1.0f, 0.0f));
			uvs.push_back(glm::vec2(1.0f, 1.0f));

			indices.push_back(0); indices.push_back(1); indices.push_back(2);
			indices.push_back(2); indices.push_back(1); indices.push_back(3);

			mesh.addData(positions, indices, uvs, true);

		/*	float ab = 0.0f;

			positions.clear();
			positions.push_back(glm::vec3(-fieldWidth, ab, -fieldDepth));
			positions.push_back(glm::vec3(-fieldWidth, ab, fieldDepth * 3));
			positions.push_back(glm::vec3(fieldWidth * 3, ab, -fieldDepth));
			positions.push_back(glm::vec3(fieldWidth * 3, ab, fieldDepth * 3));*/

			mesh2.addData(positions, indices, uvs, true);
#endif

			texture = new Texture("Render/res/textures/grid.jpg", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			//texture = new Texture("", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

			shader.setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			
			camera = new Camera(window, glm::vec3(0.0f, 0.0f, 3.0f));
	//		camera->rotateModel(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//		camera->scaleModel(glm::vec3(1.1f, 1.1f, 1.1f));
	//		camera->rotateModel(3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	//		camera->translateModel(glm::vec3(-1.5f, 1.0f, -1.5f));
	//		camera->translateModel(glm::vec3(0, 0, 0));
		}

		void input(double dt)
		{
			camera->input(dt);
		}

		glm::mat4 modela;
		void update(double dt)
		{
			static float temp = 0.0f;
			temp += dt;
			float a = sin(temp*1.5);
			float b = a / 0.9f + 1;
			//texture->setColor(glm::vec4(sin(temp), -sin(temp), sin(temp), 1.0f));
			//window.setClearColor(glm::vec4(sin(temp), sin(temp), sin(temp), sin(temp)));
			
			//modela = glm::translate(glm::rotate(glm::mat4(), glm::radians(90.0f * sin(a)) , glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(0.0f, -1.0f, 0.0f));
			//modela = glm::rotate(glm::mat4(), glm::radians(100.0f * sin(a)), glm::vec3(0.0f, 1.0f, 0.0f));
			modela = glm::translate(glm::mat4(), glm::vec3(0.0f, 1.0f, 0.0f));
			camera->update(dt);
		}

		void render()
		{
			glm::mat4 model;

			shader.bind();
			shader.updateUniforms(model, camera->getMVP(model), *texture, camera->getCameraPosition());
			mesh.draw();
			
			//camera->setModel(a);
			shader.updateUniforms(modela, camera->getMVP(modela), *texture, camera->getCameraPosition());
			mesh2.draw();
			shader.unbind();

		}

	};


}