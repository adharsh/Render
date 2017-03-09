
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

	Game::Game(Window* win)
		: window(win)
	{
		phongShader = new PhongShader();
		camera = new Camera(window, glm::vec3(0.0f, 0.01f, 0.0f));
		//window->enableMouseCursor();

		float side = 1.0f;

		Mesh* mesh = new Mesh();

		ObjLoader obj("Render/res/models/cube.obj");
		std::vector<glm::vec2> uvs = obj.getUVList();
		std::vector<glm::vec3> positions = obj.getPositionList();
		std::vector<glm::vec3> normals = obj.getNormalList();
		std::vector<GLuint> indices = obj.getIndexList();

		mesh->addData(positions, indices, uvs, normals);

 		std::vector<Renderable*> r;
		r.push_back(new Renderable(mesh, new Material(1.33f)));
		r.push_back(new Renderable(mesh, new Material(1.33f, 1.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), new Texture("Render/res/textures/Hi.png"))));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), new Texture("Render/res/textures/Coord.png"))));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), new Texture("Render/res/textures/Prime.png"))));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), new Texture("Render/res/textures/Hi.png"))));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), new Texture("Render/res/textures/Coord.png"))));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), new Texture("Render/res/textures/Prime.png"))));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), new Texture("Render/res/textures/Hi.png"))));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT, 1.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), new Texture("Render/res/textures/chalet.jpg"))));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT)));
		r.push_back(new Renderable(mesh, new Material(1.33f)));

		layer = new Layer(r);
		for (int i = 0; i < layer->size(); i++)
		{
			layer->alterRenderable(i)->alterModel()->translateMatrix(glm::vec3(i*2.0f, 0.0f, 0.0f));
			layer->alterRenderable(i)->alterModel()->rotateMatrix(glm::radians(-90.0f), glm::vec3(i*2.0f, 0.0f, 0.0f));

		}


		phongShader->setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		std::map<unsigned int, std::string> skyboxImages;
		std::string basepath = "Render/res/textures/skybox/cosmos/";
		std::string extension = ".png";
		skyboxImages[CubeMap::FRONT] = basepath + "front" + extension;
		skyboxImages[CubeMap::RIGHT] = basepath + "right" + extension;
		skyboxImages[CubeMap::LEFT] = basepath + "left" + extension;
		skyboxImages[CubeMap::TOP] = basepath + "top" + extension;
		skyboxImages[CubeMap::BOTTOM] = basepath + "bottom" + extension;
		skyboxImages[CubeMap::BACK] = basepath + "back" + extension;

		skybox = new CubeMap(skyboxImages, 500);
		text = new Text((float)window->getWidth(), (float)window->getHeight(), "Render/res/fonts/arial.ttf");
		screen = new ScreenBuffer(window->getWidth(), window->getHeight(), window->getClearColor(), false, false);
	}

	void Game::input(double dt)
	{
		camera->input(dt);
	}

	void Game::update(double dt)
	{
		camera->update(dt);

		for (int i = 0; i < layer->size(); i++)
		{
		//	layer->alterRenderable(i)->alterModel()->rotateMatrix(glm::radians(dt*1000.0f), glm::vec3(i*2.0f, 0.0f, 0.0f));
		}
	}

	void Game::render()
	{
		glm::mat4 transformProjectionView = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

		ScreenBuffer::clearBuffer(true, true, false);
		ScreenBuffer::enableDepthTest();

		screen->drawToTexture();
		layer->draw(transformProjectionView, camera->getCameraPosition(), *phongShader, *skybox);
		skybox->draw(transformProjectionView);
		screen->drawToScreen();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Game::postProcessing()
	{
		text->draw("Game Engine", 0.0f, window->getHeight() - text->getMaxCharHeight(), 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	
	}

}

/*
Allocate memory for things that last lifetime of program "beyond/outside brackets" of that method

game and window don't have to be allocated since its not used "beyond/outside brackets" of main
materials, meshes, textures, and renderables have to be allocated
*/