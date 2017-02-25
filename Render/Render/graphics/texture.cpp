#include <iostream>

#include "Texture.h"

#include "../utils/FileUtils.h"

namespace ginkgo {

	std::string Texture::whitepixelfilepath = "Render/res/textures/white.png";

	Texture::Texture(const std::string& path)
		: filepath(path)
	{
		BYTE* pixels = FileUtils::loadImage(filepath.c_str(), &width, &height);
		GLenum err;
		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			std::cout << err;
			std::cout << "Error loading texture. 1" << std::endl;
			system("pause");

		}
		glGenTextures(1, &tid);
		glBindTexture(GL_TEXTURE_2D, tid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
		err = glGetError();
		glBindTexture(GL_TEXTURE_2D, 0);
		if (err != GL_NO_ERROR)
		{
			std::cout << err << std::endl << tid << std::endl;
			std::cout << "Error loading texture. 2" << std::endl;
			system("pause");
		}

		delete[] pixels;
	}

	Texture::~Texture()
	{ }

}