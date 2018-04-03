
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

		float side = 1.0f;

		Mesh* cmesh = new Mesh();
		ObjLoader obj("Render/res/models/cube.obj");
		cmesh->addData(obj.getPositionList(), obj.getIndexList(), obj.getUVList(), obj.getNormalList());

		Mesh* pmesh = new Mesh();
		ObjLoader obj2("Render/res/models/plane.obj");
		pmesh->addData(obj2.getPositionList(), obj2.getIndexList(), obj2.getUVList(), obj2.getNormalList());

		Renderable* cube = new Renderable(cmesh, new Material(Material::REFLECT));
		cube->alterModel().translateMatrix(glm::vec3(1.0f, 0.001f, 0.0f));
		Renderable* floor = new Renderable(pmesh, new Material(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f), new Texture()));

		layer = new Layer({ cube, floor });
		//layer = new Layer({ cube});
		layer->alterModel().translateMatrix(glm::vec3(0.0f, -1.0f, -3.0f));
		phongShader->setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

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

		for (int i = 0; i < layer->size(); i++)
		{
			layer->alterModel().rotateMatrix(glm::radians(dt * 10.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		}
	}

	void Game::render()
	{
		glm::mat4 transformProjectionViewCamera = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

		ScreenBuffer::initalize();
		//screen->drawToTexture();

		////Draw Cube
		//layer->alterRenderable(0)->alterModel().newTranslateMatrix(glm::vec3(0.0f, 0.001f, 0.0f));
		////layer->drawSingle(0, transformProjectionViewCamera, camera->getCameraPosition(), *phongShader, *skybox);

		////Draw Floor
		//glEnable(GL_STENCIL_TEST);
		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		//glStencilMask(0xFF);
		//glDepthMask(GL_FALSE);
		//glClear(GL_STENCIL_BUFFER_BIT);
		////layer->drawSingle(1, transformProjectionViewCamera, camera->getCameraPosition(), *phongShader, *skybox);

		////Draw cube reflection
		//glStencilFunc(GL_EQUAL, 1, 0xFF);
		//glStencilMask(0x00);
		//glDepthMask(GL_TRUE);
		//layer->alterRenderable(0)->alterModel().newTranslateMatrix(glm::vec3(0.0f, -1.001f, 0.0f));
		////layer->drawSingle(0, transformProjectionViewCamera, camera->getCameraPosition(), *phongShader, *skybox);
		//glDisable(GL_STENCIL_TEST);
	
		layer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *phongShader, *skybox);
		skybox->draw(transformProjectionViewCamera);
		//screen->drawTextureToScreen();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Game::postProcessing()
	{
		text->draw("Game Engine", 0.0f, window.getHeight() - text->getMaxCharHeight(), 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	}

}