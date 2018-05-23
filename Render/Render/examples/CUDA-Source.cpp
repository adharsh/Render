/***************************** Main.cpp *****************************/
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <iterator>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Render/graphics/Window.h"
#include "Render/Engine.h"
#include "Render/Game.h"

#include "Render/utils/ObjLoader.h"

#include "Render/cuda/Lensing.cuh"

#include "Render/utils/FileUtils.h"

using namespace ginkgo;

/*
change Lensing.cu -> N
change lensFragment.fs -> n = N-2
*/


int main()
{

	auto start = std::chrono::steady_clock::now();


	Window window = Window("Render", 1200, 600, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	Game game(window);

	game.render();
	FileUtils::screenshot(window.getWidth(), window.getHeight());
	window.update();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		std::cout << "OpenGL Error: " << error << " in Engine.cpp, most likely game.render()" << std::endl;



	auto end = std::chrono::steady_clock::now();
	std::cout << "Duration in nanoseconds: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "\n";
	std::cout << "Duration in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "\n";
	//system("sleep 0.5");
	system("pause");

	return 0;
}

int main0()
{
	lensing();

	return 0;
}
/********************************************************************/

/***************************** Game.cpp *****************************/
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

		std::vector<glm::vec3> positions = obj.getPositionList();
		std::vector<glm::vec2> uvs = obj.getUVList();

		lensShader = new LensShader();
		//when creating Renderable, pass in 2.0f as refractive index in LensLayer
		lensLayer = new LensLayer({ new Renderable(lensMesh, new Material(new Texture())) });
		lensLayer->alterRenderable(0)->alterModel().newTranslateMatrix(glm::vec3(0.0f, 0.0f, -0.5f));
		//	lensLayer->alterRenderable(0)->alterModel().rotateMatrix(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		std::map<unsigned int, std::string> skyboxImages;
		std::string singlePath = "Render/res/textures/grid.jpg";
		skyboxImages[CubeMap::BACK] = skyboxImages[CubeMap::BOTTOM] = skyboxImages[CubeMap::TOP] = skyboxImages[CubeMap::LEFT] = skyboxImages[CubeMap::RIGHT] = skyboxImages[CubeMap::FRONT] = singlePath;
		skybox = new CubeMap(skyboxImages, 500);
	}

	void Game::render()
	{
		glm::mat4 transformProjectionViewCamera = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

		ScreenBuffer::initalize();
		screen->drawToTexture();

		lensLayer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *lensShader, *skybox);
		skybox->draw(transformProjectionViewCamera);

		//ScreenBuffer::drawAsWireframe();
		screen->drawTextureToScreen();

	}

	void Game::input(double dt)
	{	}

	void Game::update(double dt)
	{	}

	void Game::postProcessing()
	{	}

}

/********************************************************************/

/***************************** Engine.cpp *****************************/
#include <chrono>
#include <thread>
#include <iostream>

#include "Engine.h"

#include "graphics/Window.h"
#include "Game.h"
#include "Time.h"

namespace ginkgo {

	const double Engine::FRAME_CAP = 5000.0;

	Engine::Engine(Game& game, Window& window)
		: isRunning(false), window(window), game(game)
	{ }

	void Engine::start()
	{
		if (isRunning)
			return;

		run();
	}

	void Engine::stop()
	{
		if (!isRunning)
			return;

		isRunning = false;
	}

	void Engine::run()
	{
		isRunning = true;

		int frames = 0;
		long frameCounter = 0;

		const double frameTime = 1.0 / FRAME_CAP;

		auto lastTime = Time::getTime();
		double unprocessedTime = 0;

		//while (isRunning)
		//{
		//	bool render = false;

		//	auto startTime = Time::getTime();
		//	auto passedTime = Time::getDuration(startTime, lastTime);
		//	lastTime = startTime;

		//	unprocessedTime += passedTime / (double) Time::SECOND;
		//	frameCounter += passedTime;

		//	while (unprocessedTime > frameTime)
		//	{
		//		render = true;

		//		unprocessedTime -= frameTime;

		//		if (game.gameOver() || window.closed())
		//			stop();

		//		Time::setDelta(frameTime);

		//		game.input(Time::getDelta());
		//		game.update(Time::getDelta());

		//		if (frameCounter >= Time::SECOND)
		//		{
		//			//std::cout << frames << std::endl;
		//			frames = 0;
		//			frameCounter = 0;
		//		}
		//	}

		//	if (render)
		//	{
		//		this->render();
		//		frames++;
		//	}
		//	else
		//	{
		//		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		//	}
		//}

		while (isRunning)
		{
			game.input(0.01);
			game.update(0.01);
			render();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		cleanUp();
	}

	void Engine::render()
	{
		//window->clear();//do clear stuff in render

		game.render(); //3D
		game.postProcessing();// 2D
		GLenum error = glGetError();

		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << " in Engine.cpp, most likely game.render()" << std::endl;

		window.update();
		error = glGetError();

		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << " in Engine.cpp, most likely window.update()" << std::endl;
	}

	void Engine::cleanUp()
	{

	}

}
/********************************************************************/