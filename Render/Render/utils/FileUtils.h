#pragma once 

#include <string>

#include <GL/glew.h>
#include <FreeImage/FreeImage.h>

namespace ginkgo {

	class Mesh;

	class FileUtils
	{
	public:
		static std::string read_file(const char* filepath);
		static Mesh* loadMesh(const std::string& filepath);
		static BYTE* loadImage(const char* filename, GLsizei* width, GLsizei* height, double rotationAngleInDegrees = 0);

	};


}