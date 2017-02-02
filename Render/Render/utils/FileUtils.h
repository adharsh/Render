#pragma once 
#include <string>

#include <FreeImage/FreeImage.h>

#include "../graphics/Mesh.h"

namespace ginkgo {

		class FileUtils
		{
		public:
			static std::string read_file(const char* filepath);
			static Mesh* loadMesh(std:: string filepath);
			static BYTE* loadImage(const char* filename, GLsizei* width, GLsizei* height);

		};


}