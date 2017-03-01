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
	//float a[] = {
	//-0.5f, -0.5f, -0.5f,	
	//	0.5f, -0.5f, -0.5f,	
	//	0.5f, 0.5f, -0.5f,	
	//	0.5f, 0.5f, -0.5f,	
	//	-0.5f, 0.5f, -0.5f,	
	//	-0.5f, -0.5f, -0.5f,

	//	-0.5f, -0.5f, 0.5f,	
	//	0.5f, -0.5f, 0.5f,	
	//	0.5f, 0.5f, 0.5f,	
	//	0.5f, 0.5f, 0.5f,	
	//	-0.5f, 0.5f, 0.5f,	
	//	-0.5f, -0.5f, 0.5f,	

	//	-0.5f, 0.5f, 0.5f,	
	//	-0.5f, 0.5f, -0.5f,	
	//	-0.5f, -0.5f, -0.5f,
	//	-0.5f, -0.5f, -0.5f,
	//	-0.5f, -0.5f, 0.5f,	
	//	-0.5f, 0.5f, 0.5f,	

	//	0.5f, 0.5f, 0.5f,	
	//	0.5f, 0.5f, -0.5f,	
	//	0.5f, -0.5f, -0.5f,	
	//	0.5f, -0.5f, -0.5f,	
	//	0.5f, -0.5f, 0.5f,	
	//	0.5f, 0.5f, 0.5f,	

	//	-0.5f, -0.5f, -0.5f,
	//	0.5f, -0.5f, -0.5f,	
	//	0.5f, -0.5f, 0.5f,	
	//	0.5f, -0.5f, 0.5f,	
	//	-0.5f, -0.5f, 0.5f,	
	//	-0.5f, -0.5f, -0.5f,

	//	-0.5f, 0.5f, -0.5f,	
	//	0.5f, 0.5f, -0.5f,	
	//	0.5f, 0.5f, 0.5f,	
	//	0.5f, 0.5f, 0.5f,	
	//	-0.5f, 0.5f, 0.5f,	
	//	-0.5f, 0.5f, -0.5f
	//};
	//std::vector<float> b(std::begin(a), std::end(a));

	//for (int i = 0; i < b.size(); i++)
	//	b[i] *= 2.0f;

	//for (int i = 0; i < b.size(); i += 3) 
	//	std::cout << b[i] << " " << b[i+1] << " " << b[i+2] << std::endl;
	//system("pause");

	Window window = Window("Render", 800, 600, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	//Window window = Window("Render", 1700, 900, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	//Window window = Window("Render", 500, 500, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	//Window window = Window("Render", 1000, 1000, glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	Game game = Game(&window);

	Engine engine = Engine(&game, &window);
	engine.start();

	return 0;
}

/*

	int* c = new int[5];
	c[0] = 1;
	c[1] = 1;
	c[2] = 2;
	c[3] = 3;
	c[4] = 4;

*/