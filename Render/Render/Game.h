#pragma once

namespace ginkgo {

	class Window;
	class Layer;
	class Camera;
	class CubeMap;
	class PhongShader;
	class ReflectionShader;

	class Game
	{
	private:
		Window* window;
		Layer* layer;
		Camera* camera;
		CubeMap* skybox;
		ReflectionShader* reflectionShader;
		PhongShader* phongShader;
	public:
		Game(Window* window);

		void input(double dt);
		void update(double dt);

		void render();
		void postProcessing();

	};


}
