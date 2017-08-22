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

using namespace ginkgo;

int main()
{
	//Window window = Window("Render", 800, 600, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	Window window = Window("Render", 1200, 600, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	//Window window = Window("Render", 1920, 1080, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	//Window window = Window("Render", 1700, 900, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	//Window window = Window("Render", 500, 500, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	//Window window = Window("Render", 1000, 800, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	Game game(window);
	Engine engine = Engine(game, window);
	engine.start();

	return 0;
}


//#include <iomanip>
//void main()
//{
//	double a[] = { 5.00001,5,23,34.24572084975948375,5,2,25,45,52,2,5 };
//	writeBOOMFast("lol.txt", a, sizeof(a) / sizeof(double));
//
//	double* b = readBOOMFast("lol.txt", sizeof(a) / sizeof(double));
//
//	for (int i = 0; i < sizeof(a) / sizeof(double); i++)
//		std::cout << std::setprecision(100) << b[i] << std::endl;   
//
//	system("pause");
//}


/*

	int* c = new int[5];
	c[0] = 1;
	c[1] = 1;
	c[2] = 2;
	c[3] = 3;
	c[4] = 4;

*/