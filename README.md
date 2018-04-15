# 3D OpenGL Rendering Engine - Ginkgo

## Gravitational Lensing Simulation

Click images below for live demos:
| [![](https://raw.githubusercontent.com/adharsh/Render/master/Render/Render/examples/Lensing1.png)](https://youtu.be/tGgYBnis0a4) | [![](https://raw.githubusercontent.com/adharsh/Render/master/Render/Render/examples/Lensing2.png)](https://youtu.be/eBP8cWs_0nE) | [![](https://raw.githubusercontent.com/adharsh/Render/master/Render/Render/examples/Lensing3.png)](https://youtu.be/_rSjCXfAhrY) |
| --- | --- | -- |
| [Using data from MROBS project](http://galformod.mpa-garching.mpg.de/mrobs/browser/) | [Simulation with Grid image](https://raw.githubusercontent.com/adharsh/Render/master/Render/Render/res/textures/grid.jpg) | [Simulation with seas skybox](https://github.com/adharsh/Render/tree/master/Render/Render/res/textures/skybox/sea)|

## Engine Examples

Still Images:
| ![](https://raw.githubusercontent.com/adharsh/Render/master/Render/Render/examples/Chalet.bmp) | ![](https://raw.githubusercontent.com/adharsh/Render/master/Render/Render/examples/Monkeys.bmp) | ![](https://raw.githubusercontent.com/adharsh/Render/master/Render/Render/examples/Monkey-EdgeDetection.bmp) | ![](https://raw.githubusercontent.com/adharsh/Render/master/Render/Render/examples/Chalet-Emboss.bmp) | 
| --- | --- | --- | --- |  

Click images below for live demos:
| ![Saucy Spheres](http://img.youtube.com/vi/4rv2EFr_F6A/0.jpg)](https://youtu.be/4rv2EFr_F6A) | ![Chalet Shenanigans](http://img.youtube.com/vi/4yNtjyNLUzE/0.jpg)](https://youtu.be/4yNtjyNLUzE) | ![Sphere Showdown](http://img.youtube.com/vi/FmBiqfn8mEI/0.jpg)](https://youtu.be/FmBiqfn8mEI) | ![Monkey Madness](http://img.youtube.com/vi/zWvETIkqXwE/0.jpg)](https://youtu.be/zWvETIkqXwE) | ![Tango Toruses](http://img.youtube.com/vi/l-Jdh8Ou3OI/0.jpg)](https://youtu.be/l-Jdh8Ou3OI) |
| --- | --- | --- | --- | --- |

## Capabilities:

## Basic Documentation

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
	
	//If drawing to single texture, also include this line:
	screen->drawToTexture();

	//Initalize drawing to screen	
	ScreenBuffer::initalize();	
	//Get camera matrix
	glm::mat4 transformProjectionViewCamera = camera->getProjection() * camera->getView() * camera->getCameraPositionTranslation();

	/*
		Have rendering code here
	*/

	//If drawing to single texture, also include this line:
	screen->drawTextureToScreen();
}
```


Rendering code involves several aspects. The layer must call the `draw` function and pass in a `Camera` model matrix for the user's viewpoint, a `PhongShader` for lighting, and a `CubeMap` for a skybox and environmental mapping. For the lensing simulation, a `LensShader` can also be passed in.