#include <iostream>

#include "Texture.h"

#include "../utils/FileUtils.h"

namespace ginkgo {

	std::string Texture::whitepixelfilepath = "Render/res/textures/white.png";

	Texture::Texture(const glm::vec4& color, const std::string& path)
		: fileName(path), color(color)
	{
		tid = load();

		this->specularIntensity = 2;
		this->specularPower = 32;
	}

	Texture::Texture(const glm::vec4& color, float specularIntensity, float specularPower, const std::string& path)
		: Texture(color, path)
	{
		this->specularIntensity = specularIntensity;
		this->specularPower = specularPower;
	}
	
	Texture::~Texture()
	{ }

	GLuint Texture::load()
	{
		BYTE* pixels = FileUtils::loadImage(fileName.c_str(), &width, &height);
		GLenum err;
		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			std::cout << err;
			std::cout << "Error loading texture. 1" << std::endl;
			system("pause");

		}
		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
		err = glGetError();
		glBindTexture(GL_TEXTURE_2D, 0);
		if (err != GL_NO_ERROR)
		{
			std::cout << err << std::endl << result << std::endl;
			std::cout << "Error loading texture. 2" << std::endl;
			system("pause");
		}

		delete[] pixels;
		return result;
	}

}