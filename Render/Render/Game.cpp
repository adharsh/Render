
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

namespace ginkgo {

	Game::Game(Window* win)
		: window(win)
	{
		phongShader = new PhongShader();
		camera = new Camera(window, glm::vec3(0.0f, 0.01f, 0.0f));
		//window->disableMouseCursor();
		window->setMousePosition(window->getWidth() / 2.0f, window->getHeight() / 2.0f);

		float side = 1.0f;

		Mesh* mesh = new Mesh();

		ObjIntermediate obj;
		obj.LoadObj("Render/res/models/sphere.obj");
		std::vector<glm::vec2> uvs = obj.getUVList();
		std::vector<glm::vec3> positions = obj.getVertexList();
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
		//mesh->addDataLOL();

		std::vector<Renderable*> r;

		r.push_back(new Renderable(mesh, new Material(Material::REFLECT)));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT, new Texture("Render/res/textures/Hi.png"))));
		r.push_back(new Renderable(mesh, new Material(new Texture("Render/res/textures/prime.png"))));
		r.push_back(new Renderable(mesh, new Material(Material::REFLECT)));
		r.push_back(new Renderable(mesh, new Material(1.33f)));
		r.push_back(new Renderable(mesh, new Material(new Texture("Render/res/textures/coord.png"))));

		layer = new Layer(r);
		layer->alterModel()->translateMatrix(glm::vec3(-3, 0, -5));
		for (int i = 0; i < layer->getSize(); i++)
		{
			layer->alterRenderable(i)->alterModel()->translateMatrix(glm::vec3(i*2, 0, 0.0f));
		}
		layer->alterModel()->rotateMatrix(glm::radians(90.0f), glm::vec3(1, 0, 0.0f));

		//CUBE with planes
		//layer->alterRenderable(1)->alterModel()->translateMatrix(glm::vec3(0.0f, 0.0f, -1.0f));
		//layer->alterRenderable(1)->alterModel()->rotateMatrix(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//layer->alterRenderable(2)->alterModel()->translateMatrix(glm::vec3(0.0f, 1.0f, 0.0f));
		//layer->alterRenderable(3)->alterModel()->rotateMatrix(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		//layer->alterRenderable(4)->alterModel()->rotateMatrix(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//layer->alterRenderable(5)->alterModel()->translateMatrix(glm::vec3(1.0f, 0.0f, 0.0f));
		//layer->alterRenderable(5)->alterModel()->rotateMatrix(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));


		phongShader->setAmbientLight(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

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
		//layer->alterRenderable(0)->alterModel()->rotateMatrix(glm::radians(dt*100.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		static double t = 0;
		t += dt;
		//	for(int i = 0; i < layer->getSize(); i++)
		//		layer->alterModel()->rotateMatrix(glm::radians((i+1)*dt*75.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			//for (int i = 0; i < 4; i++)
			//{
			//	for (int a = 0; a < 4; a++)
			//		std::cout << layer->alterRenderable(0)->getModel()[i][a] << " ";
			//	std::cout << std::endl;
			//}


			//for (int i = 0; i < layer->getSize(); i++)
			//	layer->alterRenderable(i)->alterModel()->rotateMatrix(glm::radians((i * 10 + 10)*dt*10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		camera->update(dt);
	}

	void Game::render()
	{
		glm::mat4 transformProjectionView = camera->getProjection() * camera->getView();
		layer->draw(transformProjectionView, camera->getCameraPosition(), *phongShader, skybox);
		skybox->draw(transformProjectionView);
		//layer->draw(transformProjectionView, camera->getCameraPosition(), *reflectionShader);

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