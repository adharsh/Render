#include <iostream>
#include <cmath>
#include <map>
#include <time.h>
#include <stdlib.h>

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

#include "graphics\LensLayer.h"
#include "graphics\LensMesh.h"
#include "graphics\shaders\LensShader.h"

namespace ginkgo {

	Game::Game(Window& win)
		: window(win)
	{
		isGameOver = false; 

		camera = new Camera(&window, glm::vec3(0.0f, 0.01f, 0.0f));
		screen = new ScreenBuffer(window.getWidth(), window.getHeight(), window.getClearColor(), false, false);

		LensMesh* lensMesh = new LensMesh();
		ObjLoader obj("Render/res/models/plane.obj");
		lensMesh->addData(obj.getPositionList(), obj.getIndexList(), obj.getUVList());
		lensShader = new LensShader();
		//when creating Renderable, pass in 2.0f as refractive index in LensLayer
		lensLayer = new LensLayer({ new Renderable(lensMesh, new Material(new Texture())) });
		lensLayer->alterRenderable(0)->alterModel().newTranslateMatrix(glm::vec3(0.0f, 0.0f, -2.f));
		//	lensLayer->alterRenderable(0)->alterModel().rotateMatrix(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		std::map<unsigned int, std::string> skyboxImages;
		std::string singlePath = "Render/res/textures/space.jpg";
		skyboxImages[CubeMap::BACK] = skyboxImages[CubeMap::BOTTOM] = skyboxImages[CubeMap::TOP] = skyboxImages[CubeMap::LEFT] = skyboxImages[CubeMap::RIGHT] = skyboxImages[CubeMap::FRONT] = singlePath;
		skybox = new CubeMap(skyboxImages, 500);
		
	}

	void Game::input(double dt)
	{
		camera->input(isGameOver, dt);
		//camera->lensInput(isGameOver, dt);
	}

	void Game::update(double dt)
	{
		camera->update(dt);

		static double t = 0;
		t += dt;

		lensLayer->alterRenderable(0)->alterModel().newTranslateMatrix(glm::vec3(sin(t)*8, 0.0f, -2.f));


	}

	void Game::render()
	{
		glm::mat4 transformProjectionViewCamera = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

		ScreenBuffer::initalize();
		screen->drawToTexture();
		lensLayer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *lensShader, *skybox);
		skybox->draw(transformProjectionViewCamera);
		screen->drawToScreen();

		//ScreenBuffer::drawAsWireframe();
	}

	void Game::postProcessing()
	{	}

}

/*
Allocate memory for things that last lifetime of program "beyond/outside brackets" of that method

game and window don't have to be allocated since its not used "beyond/outside brackets" of main
materials, meshes, textures, and renderables have to be allocated
*/