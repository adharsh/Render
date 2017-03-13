
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

		Mesh* mesh = new Mesh();
		ObjLoader obj("Render/res/models/sphere.obj");
		mesh->addData(obj.getPositionList(), obj.getIndexList(), obj.getUVList(), obj.getNormalList());

		std::vector<Renderable*> r;
		for (int i = 0; i < 10; i++)
			(i % 2) ? r.push_back(new Renderable(mesh, new Material(new Texture("Render/res/textures/Hi.png")))) :
			r.push_back(new Renderable(mesh, new Material(new Texture("Render/res/textures/prime.png"))));

		layer = new Layer(r);
		//layer = new Layer({ cube});
		layer->alterModel().translateMatrix(glm::vec3(0.0f, -5.0f, -30.0f));
		for (int i = 0; i < layer->size(); i++)
			layer->alterRenderable(i)->alterModel().translateMatrix(glm::vec3(i*2.0f, i*1.0f, 0.0f));

		int s = layer->size();
		for (int i = 0; i < 3; i++)
		{
			layer->addRenderable(new Renderable(mesh, new Material(1.33f)));
			layer->addRenderable(new Renderable(mesh, new Material(new Texture("Render/res/textures/Hi.png"))));
			layer->alterRenderable(s + i)->alterModel().newTranslateMatrix(glm::vec3(0.0f, 0.0f, (s + i)*1.0f));
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

		if (window.isKeyPressed(GLFW_KEY_0))
			FileUtils::screenshot(window.getWidth(), window.getHeight());

	}

	void Game::update(double dt)
	{
		camera->update(dt);

		static double t = 0;
		t += dt;

		for (int i = 0; i < layer->size(); i++)
		{
			layer->alterModel().rotateMatrix(glm::radians(dt * 10.0f), glm::vec3(-1.0f, -1.0f, 0.0f));
		}
	}

	void Game::render()
	{
		glm::mat4 transformProjectionViewCamera = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

		screen->drawToTexture();

		layer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *phongShader, *skybox);
		skybox->draw(transformProjectionViewCamera);

		screen->drawToScreen();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Game::postProcessing()
	{
		text->draw("Game Engine", 0.0f, window.getHeight() - text->getMaxCharHeight(), 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}

}

/*
Allocate memory for things that last lifetime of program "beyond/outside brackets" of that method

game and window don't have to be allocated since its not used "beyond/outside brackets" of main
materials, meshes, textures, and renderables have to be allocated
*/