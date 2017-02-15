#pragma once

#include "graphics/Window.h"
#include "Game.h"

namespace ginkgo{

	class Engine
	{
	private:
		Window& window;
		bool isRunning;
		Game game;
		static const double FRAME_CAP;
	public:
		Engine(Window& window, Game& game);
		void start();
		void stop();

	private:
		void run();
		void render();
		void cleanUp();
		
	};

}