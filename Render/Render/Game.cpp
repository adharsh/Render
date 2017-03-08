
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
#include "graphics/shaders/ReflectionShader.h"
#include "graphics/shaders/Text.h"
#include "utils/Debugging.h"
#include "graphics\shaders\ScreenBuffer.h"

namespace ginkgo {

	Game::Game(Window* win)
		: window(win)
	{
		phongShader = new PhongShader();
		camera = new Camera(window, glm::vec3(0.0f, 0.01f, 0.0f));

		float side = 1.0f;

		Mesh* mesh = new Mesh();

		ObjIntermediate obj;
		obj.LoadObj("Render/res/models/monkey.obj");
		std::vector<glm::vec2> uvs = obj.getUVList();
		std::vector<glm::vec3> positions = obj.getPositionList();
		std::vector<GLuint> indices = obj.getIndexList();

		//std::vector<glm::vec3> positions;
		//positions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		//positions.push_back(glm::vec3(0.0f, 0.0f, -side));
		//positions.push_back(glm::vec3(side, 0.0f, -side));
		//positions.push_back(glm::vec3(side, 0.0f, 0.0f));
		//std::vector<glm::vec2> uvs;
		//uvs.push_back(glm::vec2(0.0f, 0.0f));
		//uvs.push_back(glm::vec2(0.0f, 1.0f));
		//uvs.push_back(glm::vec2(1.0f, 1.0f));
		//uvs.push_back(glm::vec2(1.0f, 0.0f));
		//std::vector<GLuint> indices;
		//indices.push_back(0); indices.push_back(1); indices.push_back(2);
		//indices.push_back(2); indices.push_back(3); indices.push_back(0);

		mesh->addData(positions, indices, uvs, true);

 		std::vector<Renderable*> r;
		//for(int i = 0; i < 10; i++)
		//	r.push_back(new Renderable(mesh, new Material(1.33f)));
		//r.push_back(new Renderable(mesh, new Material(Material::REFLECT)));
		//r.push_back(new Renderable(mesh, new Material(Material::REFLECT, 5.0f, new Texture("Render/res/textures/Hi.png"))));
		//r.push_back(new Renderable(mesh, new Material(new Texture("Render/res/textures/prime.png"))));
		//r.push_back(new Renderable(mesh, new Material(new Texture("Render/res/textures/Hi.png"))));
		//r.push_back(new Renderable(mesh, new Material(1.33f, 1.0f, new Texture("Render/res/textures/Hi.png"))));
		//r.push_back(new Renderable(mesh, new Material(1.33f, 1.0f, new Texture("Render/res/textures/Hi.png"))));
		//r.push_back(new Renderable(mesh, new Material(1.33f)));
		//r.push_back(new Renderable(mesh, new Material(1.33f, 1.0f, new Texture("Render/res/textures/coord.png"))));
		r.push_back(new Renderable(mesh, new Material(1.33f)));
		//r.push_back(new Renderable(mesh, new Material(new Texture("Render/res/textures/chalet.jpg"))));

		layer = new Layer(r);
		//layer->alterRenderable(layer->size()-1)->alterModel()->rotateMatrix(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

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
		text = new Text(window->getWidth(), window->getHeight(), "Render/res/fonts/arial.ttf");
		screen = new ScreenBuffer(window->getWidth(), window->getHeight(), window->getClearColor(), false, false);

		//Debugging::print(layer->getModel());
	}

	void Game::input(double dt)
	{
		camera->input(dt);
	}

	void Game::update(double dt)
	{
		camera->update(dt);
	}

	void Game::render()
	{
		glm::mat4 translation;
		translation[3][0] = -camera->getCameraPosition().x;
		translation[3][1] = -camera->getCameraPosition().y;
		translation[3][2] = -camera->getCameraPosition().z;
		glm::mat4 transformProjectionView = camera->getProjection() * camera->getView() * translation;

		screen->bindBuffer();
		screen->clearColor(window->getClearColor());
		screen->clearBuffer(true, true, false);
		screen->enableDepthTest();
		layer->draw(transformProjectionView, camera->getCameraPosition(), *phongShader, *skybox);
		skybox->draw(transformProjectionView);

		ScreenBuffer::bindDefaultBuffer();
		screen->clearColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		screen->clearBuffer(true, false, false);
		screen->draw();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Game::postProcessing()
	{
		text->draw("Game Engine", 0.0f, window->getHeight() - 50.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	}

}

/*
Allocate memory for things that last lifetime of program "beyond/outside brackets" of that method

game and window don't have to be allocated since its not used "beyond/outside brackets" of main
materials, meshes, textures, and renderables have to be allocated
*/