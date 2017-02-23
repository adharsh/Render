#pragma once

namespace ginkgo {

	class Window;
	class Layer;
	class Camera;
	class CubeMapShader;

	class Game
	{
	private:
		Window* window;
		Layer* layer;
		Camera* camera;
		CubeMapShader* shader;
	public:
		Game(Window* window);

		void input(double dt);
		void update(double dt);

		void render();
		void postProcessing();

	};


}
