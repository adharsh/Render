#pragma once 
#include <string>

#include "../graphics/Mesh.h"

namespace ginkgo {

		class FileUtils
		{
		public:
			static std::string read_file(const char* filepath);
			static Mesh* loadMesh(std:: string filepath);

		};


}