
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

namespace ginkgo {

	Game::Game(Window& win)
		: window(win)
	{
		phongShader = new PhongShader();
		camera = new Camera(&window, glm::vec3(0.0f, 0.01f, 0.0f));

		Mesh* smesh = new Mesh();
		ObjLoader obj("Render/res/models/smooth_torus.obj");
		smesh->addData(obj.getPositionList(), obj.getIndexList(), obj.getUVList(), obj.getNormalList());

		std::vector<Renderable*> renderables;
		for (int i = 0; i < 10; i++)
			renderables.push_back(new Renderable(smesh, new Material(Material::REFLECT)));

		layer = new Layer(renderables);
		layer->alterModel().translateMatrix(glm::vec3(-6.0f, 0.0f, -10.0f));

		for (int i = 1; i <= layer->size(); i++)
			layer->alterRenderable(i - 1)->alterModel().translateMatrix(glm::vec3(i, 0, 0));

		std::map<unsigned int, std::string> skyboxImages;
		std::string basepath = "Render/res/textures/skybox/sea/";
		std::string extension = ".jpg";
		skyboxImages[CubeMap::FRONT] = basepath + "front" + extension;
		skyboxImages[CubeMap::RIGHT] = basepath + "right" + extension;
		skyboxImages[CubeMap::LEFT] = basepath + "left" + extension;
		skyboxImages[CubeMap::TOP] = basepath + "top" + extension;
		skyboxImages[CubeMap::BOTTOM] = basepath + "bottom" + extension;
		skyboxImages[CubeMap::BACK] = basepath + "back" + extension;

		skybox = new CubeMap(skyboxImages, 500);
		screen = new ScreenBuffer(window.getWidth(), window.getHeight(), window.getClearColor(), false, false);

		text = new Text(window.getWidth(), window.getHeight(), "Render/res/fonts/arial.ttf");
	}

	void Game::input(double dt)
	{
		camera->input(isGameOver, dt);
	}

	void Game::update(double dt)
	{
		camera->update(dt);

		static double t = 0;
		t += dt * 0.001;

		for (int i = 1; i <= layer->size(); i++)
		{
			layer->alterRenderable(i - 1)->alterModel().rotateMatrix(i * dt, glm::vec3(cos(t), cos(t), cos(t)));
		}
	}

	void Game::render()
	{
		glm::mat4 transformProjectionViewCamera = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

		screen->drawToTexture();
		ScreenBuffer::initalize();
		layer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *phongShader, *skybox);
		skybox->draw(transformProjectionViewCamera);
		screen->drawTextureToScreen();

		//why if this code underneath uncommmented and postProcessing commented cant see text?
		//text->draw("Game Engine", 0.0f, window.getHeight() - 50.0f, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Game::postProcessing()
	{
		text->draw("Game Engine", 0.0f, window.getHeight() - text->getMaxCharHeight(), 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}

}