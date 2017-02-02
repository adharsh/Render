#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Render/graphics/Window.h"
#include "Render/Engine.h"
#include "Render/Handle.h"
#include "Render/Game.h"

#include "Render\utils\ObjLoader.h"

using namespace ginkgo;

int main()
{

	//Window window = Window("Render", 800, 600, glm::vec4(0.4f, 0.5f, 0.5f, 1.0f));
	Window window = Window("Render", 800, 600, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));

	Engine engine = Engine(window);
	engine.start();

	return 0;
}