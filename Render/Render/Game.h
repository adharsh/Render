#pragma once

namespace ginkgo {

	class Window;
	class Layer;
	class Camera;
	class CubeMap;
	class PhongShader;
	class ReflectionShader;
	class Text;
	class ScreenBuffer;

	class LensLayer;
	class LensShader;

	class Game
	{
	private:
		bool isGameOver;
	private:
		Window& window;
		Layer* layer;
		Camera* camera;
		CubeMap* skybox;
		ReflectionShader* reflectionShader;
		PhongShader* phongShader;
		Text* text;
		ScreenBuffer* screen;

		LensShader* lensShader;
		LensLayer* lensLayer;

	public:
		Game(Window& window);

		void input(double dt);
		void update(double dt);

		void render();
		void postProcessing();

		bool gameOver() { return isGameOver; }

	};


}
