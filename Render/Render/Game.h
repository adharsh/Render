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
		Texture* texture;

		Camera* camera;
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 model;
		glm::vec3 cameraPosition;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		
		PointLight pLight1;
		PointLight pLight2;
		PointLight pLight3;

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

			/*		for (unsigned int i = 0; i < uvs.size(); i++)
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
			window.disableMouseCursor();
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
#endif

			texture = new Texture("Render/res/textures/white.png", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			//texture = new Texture("", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			DirectionalLight dLight(
				BaseLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 0.55f),
				glm::vec3(1.0f, 1.0f, 1.0f));
			//shader.setDirectionalLight(dLight);
			shader.setAmbientLight(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));

			pLight1 = PointLight(
				BaseLight(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), 1.0f),
				Attenuation(0.0f, 0.0f, 1.0f),
				glm::vec3(-4.0f, 0.0f, 7.0f));

			pLight2 = PointLight(
				BaseLight(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), 1.0f),
				Attenuation(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, 7.0f));

			pLight3 = PointLight(
				BaseLight(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), 1.0f),
				Attenuation(0.0f, 0.0f, 1.0f),
				glm::vec3(4.0f, 0.0f, 7.0f));

			shader.setPointLights({ pLight1, pLight2, pLight3 });

			camera = new Camera(window, glm::vec3(0.0f, 0.0f, 3.0f));
			camera->scaleModel(glm::vec3(1.1f, 1.1f, 1.1f));
			camera->rotateModel(3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			camera->translateModel(glm::vec3(-1.5f, 1.0f, -1.5f));
			camera->translateModel(glm::vec3(0, 0, 0));
			
			cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
			cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
			cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
			projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 1000.0f);
			view = glm::lookAt(
				cameraPosition,
				cameraPosition + cameraFront,
				cameraUp);

			GLfloat cameraSpeed = 5.0f * 700000000 * 10E-10;
			cameraPosition -= cameraSpeed * cameraFront;
			model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
			model = glm::rotate(model, 3.14f / 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::translate(model, glm::vec3(-1.5f, 1.0f, -1.5f));
		}

		void input(double dt)
		{
			camera->input(dt);
		}

		void update(double dt)
		{
			static float temp = 0.0f;
			temp += Time::getDelta();
			float a = sin(temp*1.5);
			float b = a / 0.9f + 1;
			//texture->setColor(glm::vec4(sin(temp), -sin(temp), sin(temp), 1.0f));
			//window.setClearColor(glm::vec4(sin(temp), sin(temp), sin(temp), sin(temp)));
			camera->update(dt);
			//shader.setPointLightPosition(1, glm::vec3(0, 0, a));
			//shader.setAmbientLight(glm::vec4(0.3f, 0.3f, 0.3f, 1.0f));
		}

		void render()
		{
			shader.bind();
			shader.updateUniforms(camera->getModel(), camera->getMVP(), *texture, camera->getCameraPosition());
			mesh.draw();
			shader.unbind();

		}

	};


}