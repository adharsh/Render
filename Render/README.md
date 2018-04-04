# ginkgo
# 3D OpenGL Rendering Engine 

## Gallery Galore

2 gifs to show off ability of stuff
Spheres moving cool 
Narcotic monkeys effects

###Lensing Simulation
Youtube Links
Sample Images as well

### Engine
Image Kernel Effects - edge detection, blur, and narcotic
Phong Lighting
Refraction, reflection
Loading obj file with texture -> chalet
cubemap zoom in and zoom out 
Rendering text
Spheres particle effect movement

Implemented image kernel effects for features like edge detection and gaussian blur.
• Implemented support for loading renderable objects from Wavefront obj files and textures
from various image formats.
• Implemented renderable objects to have phong lighting, reflective or refractive properties,
colors, textures, and movement using transformation matrices.
• Implemented an OpenGL Cubemap to create skyboxes.
• Implemented support for rendering text and loading different fonts.




## Basic Documentation

### Methods to change for your own applicatino
If you would like to implement your own graphics applications using this engine, you would have to edit the `Graphics.cpp` file, specifically the methods below, where `dt` is the time between the last tick to the current tick:

- `Game::Game(Window &win);`
	- Constructor: initalizes window and creates local variables, called once
- `void Game::input(double dt);`
	- Called on each tick for user input
- `void Game::render();`
	- Used for drawing each frame
- `void Game::update(double dt);`
	- Used for updating variables and called per tick
- `void Game::postProcessing();`
	- Used for rendering operations after render is called

### Introduction to usage of classes
Each renderable is something that can be drawn to the screen.
Each renderable has a mesh and a material.
A mesh consists of the objects vertices/positions, index list that specify the order of the vertices to be drawn, a UV list for the texture coordinates for texture mapping, and a normal list for lighting.
Such data can be loaded from a Wavefront obj file using the Objloader class.

Together, the code would look like this:
```c++
Mesh *cmesh = new Mesh();
ObjLoader obj("Render/res/models/cube.obj"); //filepath of obj file
cmesh->addData(obj.getPositionList(), obj.getIndexList(), obj.getUVList(), obj.getNormalList());
```

Then the renderable can be created as follows:
```c++
Renderable* cube = new Renderable(cmesh, new Material(Material::REFLECT));
```
In this example, the material passed can only reflect the light from its environment. There are no other properties to its material.
The properties of a material are:

- Reflective and Refractive, as specified by `refractiveIndex` (if `refractiveIndex` < 1 then reflect function will automatically be used)
- Base Color, as specified by `color`
- Lighting, as specified by `specularIntensity` and `specularPower`

The above could be used in any combination to create a variety of renderable objects.
This example shows 
```c++
Renderable* hi_cube = new Renderable(cmesh, new Material(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), new Texture("Render/res/textures/Hi.png")));
```

A layer is a group of renderables.
Each renderable must be placed within a layer.
A layer can be created by the following: 
```c++
Layer *layer = new Layer({ cube, hi_cube });
```
Each renderable in the layer can be changed using the index in which it was passed in;
In this example, to change the `cube`:
```c++
layer->alterRenderable(0)->alterModel().translateMatrix(glm::vec3(0.0f, -1.0f, -3.0f));
```
This retrieves `cube` and then retrieve's its model matrix and translates its matrix by the given vector.

The layer and all of its renderables can be moved together using the same `alterModel` method, which returns an object of the `Transform` class. The `Transform` class creates flexibility in changing an object's model matrix for movement. 

```c++
void Game::render()				
{	
	//Start out with:			
	//Initalize drawing to screen	
	ScreenBuffer::initalize();	
	//Get camera matrix
	glm::mat4 transformProjectionViewCamera = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

	//If drawing to single texture, also include this line:
	screen->drawToTexture();

	/*
		Have rendering code here
	*/

	//If drawing to single texture, also include this line:
	screen->drawTextureToScreen();
}
```


Rendering code involves several aspects. The layer must call the `draw` function and pass in a `Camera` model matrix for the user's viewpoint, a `PhongShader` for lighting, and a `CubeMap` for a skybox and environmental mapping. For the lensing simulation, a `LensShader` can also be passed in.

For example, a layer can be used like the followng:
```c++
	layer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *phongShader, *skybox);
```



For the lensing simulation:
```c++
	//Layer creation is different
	LensLayer* lensLayer = new LensLayer({ new Renderable(lensMesh, new Material(new Texture())) });
	lensLayer->draw(transformProjectionViewCamera, camera->getCameraPosition(), *lensShader, *skybox);
```

For updating the layer's renderables:
void Game::update(double dt)
	{
		camera->update(dt);

		for (int i = 0; i < layer->size(); i++)
		{
			layer->alterModel().rotateMatrix(glm::radians(dt * 10.0f), glm::vec3(0.0f, -1.0f, 0.0f));
		}
	}

Sample code for the use of other methods:

```c++
Camera *camera = new Camera(&window, glm::vec3(0.0f, 0.01f, 0.0f));
void Game::input(double dt)
{
	camera->input(isGameOver, dt);
}

void Game::update(double dt)
{
	camera->update(dt);

	for (int i = 0; i < layer->size(); i++)
	{
		layer->alterModel().rotateMatrix(glm::radians(dt * 10.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	}
}

Text *text = new Text(window.getWidth(), window.getHeight(), "Render/res/fonts/arial.ttf");
void Game::postProcessing()
{
	text->draw("Game Engine", 0.0f, window.getHeight() - text->getMaxCharHeight(), 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}
```