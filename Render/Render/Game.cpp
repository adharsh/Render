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

#include "graphics\LensLayer.h"
#include "graphics\LensMesh.h"
#include "graphics\shaders\LensShader.h"

namespace ginkgo {

	Game::Game(Window& win)
		: window(win)
	{
		isGameOver = false;

		camera = new Camera(&window, glm::vec3(0.0f, 0.01f, 0.0f));
		//Mesh* mesh = new Mesh();
		//ObjLoader obj("Render/res/models/sphere_square.obj");
		//mesh->addData(obj.getPositionList(), obj.getIndexList(), obj.getUVList(), obj.getNormalList());
		//phongShader = new PhongShader(); phongShader->setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		//std::vector<Renderable*> r;
		//for (int i = 0; i < 1; i++)
		//	r.push_back(new Renderable(mesh, new Material(new Texture("Render/res/textures/grid.jpg"))));
		////when creating Renderable, pass in 2.0f as refractive index in LensLayer
		//
		//layer = new Layer(r);
		//layer->alterModel().translateMatrix(glm::vec3(0.0f, 0.0f, -3.0f));
		//for (int i = 0; i < layer->getSize(); i++)
		//{
		//	layer->alterRenderable(i)->alterModel().translateMatrix(glm::vec3(i*2.0f, 0.0f, -0.0f));
		//}

		LensMesh* lensMesh = new LensMesh();
		//ObjLoader obj("Render/res/models/sphere_square.obj");
		ObjLoader obj("Render/res/models/plane.obj");
		lensMesh->addData(obj.getPositionList(), obj.getIndexList(), obj.getUVList());
		lensShader = new LensShader();
		//when creating Renderable, pass in 2.0f as refractive index in LensLayer
		lensLayer = new LensLayer({ new Renderable(lensMesh, new Material(new Texture("Render/res/textures/Normals3.bmp"))) }); // Normals4 < Normals7 < Normals6 < Normals3
		lensLayer->alterRenderable(0)->alterModel().scaleMatrix(glm::vec3(0.5f, 0.5f, 0.5f));
		lensLayer->alterRenderable(0)->alterModel().scaleMatrix(glm::vec3(10.0f, 10.0f, 10.0f));
		lensLayer->alterRenderable(0)->alterModel().rotateMatrix(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		std::map<unsigned int, std::string> skyboxImages;
		//std::string basepath = "Render/res/textures/skybox/sea/"; std::string extension = ".jpg";
		//std::string basepath = "Render/res/textures/skybox/cosmos/"; std::string extension = ".png";
		//std::string basepath = "Render/res/textures/skybox/room/"; std::string extension = ".jpeg";
		//std::string singlePath = "Render/res/textures/skybox/dot.png";
		//std::string singlePath = "Render/res/textures/newspaper.jpg";
		std::string singlePath = "Render/res/textures/grid.jpg";
		skyboxImages[CubeMap::BACK] = skyboxImages[CubeMap::BOTTOM] = skyboxImages[CubeMap::TOP] = skyboxImages[CubeMap::LEFT] = skyboxImages[CubeMap::RIGHT] = skyboxImages[CubeMap::FRONT] = singlePath;
		//skyboxImages[CubeMap::FRONT] = basepath + "front" + extension; skyboxImages[CubeMap::RIGHT] = basepath + "right" + extension; skyboxImages[CubeMap::LEFT] = basepath + "left" + extension; skyboxImages[CubeMap::TOP] = basepath + "top" + extension; skyboxImages[CubeMap::BOTTOM] = basepath + "bottom" + extension; skyboxImages[CubeMap::BACK] = basepath + "back" + extension; skyboxImages[CubeMap::FRONT] = basepath + "front" + extension;
		skybox = new CubeMap(skyboxImages, 500);
		text = new Text(window.getWidth(), window.getHeight(), "Render/res/fonts/arial.ttf");
		screen = new ScreenBuffer(window.getWidth(), window.getHeight(), window.getClearColor(), false, false);
	}

	void Game::input(double dt)
	{
		static double t = 0;
		t += dt;

		camera->input(isGameOver, dt);
		//camera->lensInput(isGameOver, dt);
		//lensLayer->alterRenderable(0)->alterModel().newTranslateMatrix(glm::vec3(sin(t), 0.0f, 0.0f));
		//lensLayer->alterRenderable(0)->alterModel().rotateMatrix(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void Game::update(double dt)
	{
		static double t = 0;
		t += dt / 1.0f;
		double x = sin(t);
		x *= 0.50;

		camera->update(dt);
		lensLayer->alterRenderable(0)->alterModel().newTranslateMatrix(glm::vec3(x, 0, 0));
		lensLayer->alterRenderable(0)->alterModel().translateMatrix(glm::vec3(0.0f, 0.0f, -0.7f));
		lensLayer->alterRenderable(0)->alterModel().rotateMatrix(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	void Game::render()
	{
		glm::mat4 transformProjectionViewCamera = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

		ScreenBuffer::initalize();
		screen->drawToTexture();

		//layer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *phongShader, *skybox);
		lensLayer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *lensShader, *skybox);
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