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
#include "graphics/Renderable.h"
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

			Texture* t0 = new Texture("Render/res/textures/Hi.png", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			Texture* t1 = new Texture("Render/res/textures/white.png", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			Texture* t2 = new Texture("Render/res/textures/coord.jpg", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			Texture* t3 = new Texture("Render/res/textures/coord.png", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
			Texture* t4 = new Texture("Render/res/textures/prime.png", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
					
			Renderable* r0 = new Renderable(mesh, *t0);
			Renderable* r1 = new Renderable(mesh, *t0);
			Renderable* r2 = new Renderable(mesh, *t1);
			Renderable* r3 = new Renderable(mesh, *t2);
			Renderable* r4 = new Renderable(mesh, *t2);
			Renderable* r5 = new Renderable(mesh, *t3);
			Renderable* r6 = new Renderable(mesh, *t4);
			
			std::vector<Renderable*> r = { r0, r1, r2, r3, r4, r5, r6};

			layer = new Layer(r, shader, camera);

			layer->addRenderable(new Renderable(mesh, *t0));
			layer->addRenderable(new Renderable(mesh, *t2));
			layer->addRenderable(new Renderable(mesh, *t3));
			layer->addRenderable(new Renderable(mesh, *t4));

			r0->alterTexture().setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

			float a = 0;
			for (int i = 0; i < layer->getSize(); i++)
			{
				layer->alterRenderable(i)->translateModel(glm::vec3(0.0f, a, 0.0f));
				a += 0.2f;
			}

			shader->setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		void input(double dt)
		{
			camera->input(dt);
		}

		void update(double dt)
		{
			//texture->setColor(glm::vec4(sin(temp), -sin(temp), sin(temp), 1.0f));
			//window.setClearColor(glm::vec4(sin(temp), sin(temp), sin(temp), sin(temp)));
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