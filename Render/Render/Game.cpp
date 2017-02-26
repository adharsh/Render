
#include <iostream>
#include <cmath>
#include <map>

#include "graphics/Window.h" //window include must be before glfw include to prevent #error: gl.h included before glew.h
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Game.h"

#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "graphics/shaders/PhongShader.h"
#include "graphics/shaders/CubeMap.h"
#include "graphics/Camera.h"
#include "graphics/Renderable.h"
#include "graphics/Layer.h"
#include "utils/ObjLoader.h"
#include "graphics/Transform.h"

namespace ginkgo {

	Game::Game(Window* win)
		: window(win)
	{
		PhongShader* shader = new PhongShader();
		camera = new Camera(window, glm::vec3(0.0f, 0.01f, 0.0f));
		//window->disableMouseCursor();
		window->setMousePosition(window->getWidth() / 2.0f, window->getHeight() / 2.0f);

		float side = 1.0f;

		Mesh* mesh = new Mesh();
		std::vector<glm::vec3> positions;
		positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		positions.push_back(glm::vec3(0.0f, 0.0f, -side));
		positions.push_back(glm::vec3(side, 0.0f, -side));
		positions.push_back(glm::vec3(side, 0.0f, 0.0f));
		std::vector<glm::vec2> uvs;
		uvs.push_back(glm::vec2(0.0f, 0.0f));
		uvs.push_back(glm::vec2(0.0f, 1.0f));
		uvs.push_back(glm::vec2(1.0f, 1.0f));
		uvs.push_back(glm::vec2(1.0f, 0.0f));
		std::vector<GLuint> indices;
		indices.push_back(0); indices.push_back(1); indices.push_back(2);
		indices.push_back(2); indices.push_back(3); indices.push_back(0);
		mesh->addData(positions, indices, uvs, true);

		Texture* t0 = new Texture("Render/res/textures/Hi.png");
		Texture* t1 = new Texture("Render/res/textures/prime.png");

		Material* m0 = new Material(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), t0);
		Material* m1 = new Material(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), t0);
		Material* m2 = new Material(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), t1);

		std::vector<Renderable*> r;
		for (int i = 0; i < 4; i++)
			r.push_back(new Renderable(mesh, m0));
		r.push_back(new Renderable(mesh, m1));
		r.push_back(new Renderable(mesh, m2));
		layer = new Layer(r, shader);

		for (int i = 0; i < layer->getSize(); i++)
			layer->alterRenderable(i)->alterModel()->translateMatrix(glm::vec3(0, i / 2.0f, 0));

		shader->setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		std::map<unsigned int, const char*> skyboxImages;
		skyboxImages[CubeMap::LEFT] = "Render/res/textures/skybox/left.jpg";
		skyboxImages[CubeMap::RIGHT] = "Render/res/textures/skybox/right.jpg";
		skyboxImages[CubeMap::TOP] = "Render/res/textures/skybox/top.jpg";
		skyboxImages[CubeMap::FRONT] = "Render/res/textures/skybox/front.jpg";
		skyboxImages[CubeMap::BOTTOM] = "Render/res/textures/skybox/bottom.jpg";
		skyboxImages[CubeMap::BACK] = "Render/res/textures/skybox/back.jpg";
		
		skybox = new CubeMap(skyboxImages, 500);

	}

	void Game::input(double dt)
	{
		camera->input(dt);
	}

	void Game::update(double dt)
	{
		//texture->setColor(glm::vec4(sin(temp), -sin(temp), sin(temp), 1.0f));
		//window->setClearColor(glm::vec4(1, 1, 1, 1));
		dt = 0;
		layer->alterModel()->rotateMatrix(glm::radians(dt*100.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		for (int i = 0; i < layer->getSize(); i++)
			layer->alterRenderable(i)->alterModel()->rotateMatrix(glm::radians((i * 10 + 10)*dt*10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		camera->update(dt);
	}

	void Game::render()
	{
		glm::mat4 transformProjectionView = camera->getProjection() * camera->getView();
		layer->draw(transformProjectionView, camera->getCameraPosition());
		skybox->draw(transformProjectionView);
	}

	void Game::postProcessing()
	{

	}

}

/*
Allocate memory for things that last lifetime of program "beyond/outside brackets" of that method

game and window don't have to be allocated since its not used "beyond/outside brackets" of main
materials, meshes, textures, and renderables have to be allocated



*/