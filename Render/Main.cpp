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