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
#include "graphics/Layer.h"
#include "graphics/shaders/Text.h"
#include "utils/Debugging.h"
#include "graphics\shaders\ScreenBuffer.h"
#include "utils\FileUtils.h"

namespace ginkgo {

	Game::Game(Window& win)
		: window(win)
	{
		isGameOver = false;

		phongShader = new PhongShader();
		camera = new Camera(&window, glm::vec3(0.0f, 0.01f, 0.0f));
		//window.enableMouseCursor();

		Mesh* mesh = new Mesh();
		ObjLoader obj("Render/res/models/sphere_square.obj");
		mesh->addData(obj.getPositionList(), obj.getIndexList(), obj.getUVList(), obj.getNormalList());

		std::vector<Renderable*> r;
		for (int i = 0; i < 1; i++)
			r.push_back(new Renderable(mesh, new Material(new Texture("Render/res/textures/grid.jpg"))));

		layer = new Layer(r);
		layer->alterModel().translateMatrix(glm::vec3(0.0f, 0.0f, -3.0f));
		for (int i = 0; i < layer->getSize(); i++)
		{
			layer->alterRenderable(i)->alterModel().translateMatrix(glm::vec3(i*2.0f, 0.0f, -0.0f));
		}

		phongShader->setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		std::map<unsigned int, std::string> skyboxImages;
		std::string basepath = "Render/res/textures/skybox/sea/";
		std::string extension = ".jpg";
		std::string singlePath = "Render/res/textures/skybox/dot.png";
		//skyboxImages[CubeMap::BACK] = skyboxImages[CubeMap::BOTTOM] = skyboxImages[CubeMap::TOP] = skyboxImages[CubeMap::LEFT] = skyboxImages[CubeMap::RIGHT] = skyboxImages[CubeMap::FRONT] = singlePath;
		skyboxImages[CubeMap::FRONT] = basepath + "front" + extension; skyboxImages[CubeMap::RIGHT] = basepath + "right" + extension; skyboxImages[CubeMap::LEFT] = basepath + "left" + extension; skyboxImages[CubeMap::TOP] = basepath + "top" + extension; skyboxImages[CubeMap::BOTTOM] = basepath + "bottom" + extension; skyboxImages[CubeMap::BACK] = basepath + "back" + extension;

		skybox = new CubeMap(skyboxImages, 500);
		text = new Text(window.getWidth(), window.getHeight(), "Render/res/fonts/arial.ttf");
		screen = new ScreenBuffer(window.getWidth(), window.getHeight(), window.getClearColor(), false, false);
	}

	void Game::input(double dt)
	{
		camera->input(isGameOver, dt);
	}

	void Game::update(double dt)
	{
		camera->update(dt);

		static double t = 0;
		t += dt;

		for (int i = 0; i < layer->getSize(); i++)
		{
			layer->alterRenderable(i)->alterModel().rotateMatrix(glm::radians(i * dt * 3.0f), glm::vec3(-1.0f, -1.0f, 0.0f));
			//layer->alterModel().rotateMatrix(glm::radians(dt * 5.0f), glm::vec3(-1.0f, -1.0f, 0.0f));
		}

	}

	void Game::render()
	{
		glm::mat4 transformProjectionViewCamera = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

		ScreenBuffer::initalize();
		screen->drawToTexture();

		layer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *phongShader, *skybox);
		skybox->draw(transformProjectionViewCamera);

		screen->drawToScreen();
		//ScreenBuffer::drawAsWireframe();
	}

	void Game::postProcessing()
	{
		//text->draw("Game Engine", 0.0f, window.getHeight() - text->getMaxCharHeight(), 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}

}

/*
Allocate memory for things that last lifetime of program "beyond/outside brackets" of that method

game and window don't have to be allocated since its not used "beyond/outside brackets" of main
materials, meshes, textures, and renderables have to be allocated
*/