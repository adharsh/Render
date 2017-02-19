#pragma once

#include <iostream>
#include <cmath>

#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Time.h"
//#include "graphics/Mesh.h"
//#include "graphics/Texture.h"
//#include "graphics/shaders/PhongShader.h"
#include "utils/ObjLoader.h"
//#include "graphics\Camera.h"
//#include "graphics/Renderable.h"
#include "graphics/Layer.h"

namespace ginkgo {

	class Game
	{
	private:
		Window* window;
		Layer* layer;
		Camera* camera;

	public:
		Game(Window* win) : window(win)
		{
			PhongShader* shader = new PhongShader();
			camera = new Camera(window, glm::vec3(0.0f, 0.01f, 0.0f));
			//window.disableMouseCursor();

			float side = 1.0f;
			std::vector<glm::vec3> positions;
			std::vector<glm::vec2> uvs;
			std::vector<GLuint> indices;
			positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
			positions.push_back(glm::vec3(0.0f, 0.0f, -side));
			positions.push_back(glm::vec3(side, 0.0f, -side));
			positions.push_back(glm::vec3(side, 0.0f, 0.0f));
			uvs.push_back(glm::vec2(0.0f, 0.0f));
			uvs.push_back(glm::vec2(0.0f, 1.0f));
			uvs.push_back(glm::vec2(1.0f, 1.0f));
			uvs.push_back(glm::vec2(1.0f, 0.0f));
			indices.push_back(0); indices.push_back(1); indices.push_back(2);
			indices.push_back(2); indices.push_back(3); indices.push_back(0);

			Mesh* mesh = new Mesh();
			mesh->addData(positions, indices, uvs, true);

			Texture* t0 = new Texture(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
					
			Renderable* r0 = new Renderable(mesh, *t0);
			
			layer = new Layer({r0}, shader, camera);

			shader->setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		void input(double dt)
		{
			camera->input(dt);
		}

		void update(double dt)
		{
			//texture->setColor(glm::vec4(sin(temp), -sin(temp), sin(temp), 1.0f));
			//window->setClearColor(glm::vec4(1, 1, 1, 1));
			static float t = 0;
			t += dt * 0.000001;
			//layer->alterRenderable(0)->rotateModel(glm::radians(t), glm::vec3(1.0f, 0.0f, 0.0f));
			
			camera->update(dt);
		}

		void render()
		{
			layer->draw();
		}

	};


}