#include <iostream>
#include <Windows.h>

#include "Engine.h"
#include "Time.h"

namespace ginkgo {

	const double Engine::FRAME_CAP = 5000.0;

	Engine::Engine(Game* game, Window* window)
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

		while (isRunning)
		{
			bool render = false;

			auto startTime = Time::getTime();
			auto passedTime = Time::getDuration(startTime, lastTime);
			lastTime = startTime;

			unprocessedTime += passedTime / (double) Time::SECOND;
			frameCounter += passedTime;

			while (unprocessedTime > frameTime)
			{
				render = true;

				unprocessedTime -= frameTime;

				if (window->closed())
					stop();

				Time::setDelta(frameTime);

				game->input(Time::getDelta());
				game->update(Time::getDelta());

				if (frameCounter >= Time::SECOND)
				{
					//std::cout << frames << std::endl;
					frames = 0;
					frameCounter = 0;
				}
			}

			if (render)
			{
				this->render();
				frames++;
			}
			else
			{
				Sleep(1);
			}
		}

		cleanUp();
	}

	void Engine::render()
	{
		glGetError();
		window->clear();
		
		game->render(); //3D
		//game.postProcess(); 2D
		GLenum error = glGetError();

		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << " in Engine.cpp, most likely game.render()" << std::endl;
		
		window->update();
		error = glGetError();

		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << " in Engine.cpp, most likely window.update()" << std::endl;;
	}

	void Engine::cleanUp()
	{

	}


}