#pragma once

namespace ginkgo{
	
	class Window;
	class Game;

	class Engine
	{
	private:
		Window* window;
		bool isRunning;
		Game* game;
		static const double FRAME_CAP;
	public:
		Engine(Game* game, Window* window);
		void start();
		void stop();

	private:
		void run();
		void render();
		void cleanUp();
		
	};

}