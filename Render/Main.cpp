#include <iostream>
#include <vector>
#include <iterator>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Render/graphics/Window.h"
#include "Render/Engine.h"
#include "Render/Game.h"

#include "Render/utils/ObjLoader.h"

using namespace ginkgo;

int main()
{
	Window window = Window("Render", 800, 600, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	Game game(window);

	Engine engine = Engine(game, window);
	engine.start();

	return 0;
}