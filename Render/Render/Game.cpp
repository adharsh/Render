
#include <iostream>
#include <cmath>

#include "graphics/Window.h" //window include must be before glfw include to prevent #error: gl.h included before glew.h
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Game.h"

#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/Material.h"
#include "graphics/shaders/PhongShader.h"
#include "graphics/shaders/CubeMapShader.h"
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
		//window.disableMouseCursor();

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

		Material* t0 = new Material(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), new Texture("Render/res/textures/Hi.png"));

		Renderable* r0 = new Renderable(mesh, t0);
		layer = new Layer({ r0 }, shader);

		shader->setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		std::vector<const char*> skyboxImages;
		skyboxImages.push_back("Render/res/textures/skybox/right.jpg");
		skyboxImages.push_back("Render/res/textures/skybox/left.jpg");
		skyboxImages.push_back("Render/res/textures/skybox/top.jpg");
		skyboxImages.push_back("Render/res/textures/skybox/bottom.jpg");
		skyboxImages.push_back("Render/res/textures/skybox/front.jpg");
		skyboxImages.push_back("Render/res/textures/skybox/back.jpg");

		shaderCM = new CubeMapShader(skyboxImages, 500.0f);

		shaderCM->alterModel()->rotateMatrix(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		layer->alterRenderable(0)->alterModel()->translateMatrix(glm::vec3(0.0f, 1.0f, 0.0f));
		layer->alterRenderable(0)->alterModel()->scaleMatrix(glm::vec3((20, 20, 20)));
		layer->alterModel()->translateMatrix(glm::vec3(0.0f, 0.2f, 0.0f));
	}

	void Game::input(double dt)
	{
		camera->input(dt);
	}

	void Game::update(double dt)
	{
		//texture->setColor(glm::vec4(sin(temp), -sin(temp), sin(temp), 1.0f));
		//window->setClearColor(glm::vec4(1, 1, 1, 1));
		static float t = 0;
		t += dt * 0.001f;

		//layer->alterRenderable(0)->alterModel()->scaleMatrix(glm::vec3((t, t, t)));
		//layer->alterRenderable(0)->alterModel()->rotateMatrix(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		//layer->scaleModel(glm::vec3(1.0f + t, 1.0f + t, 1.0f + t));
		layer->alterModel()->rotateMatrix(glm::radians(t), glm::vec3(1.0f, 0.0f, 0.0f));
		//layer->alterRenderable(3)->rotateModel(glm::radians(t), glm::vec3(1.0f, 0.0f, 0.0f));
		//layer->translateModel(glm::vec3(t, 0, 0));

		camera->update(dt);
	}

	void Game::render()
	{
		glm::mat4 transformProjectionView = camera->getProjection() * camera->getView();
		layer->draw(transformProjectionView, camera->getCameraPosition());
		shaderCM->draw(transformProjectionView);
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