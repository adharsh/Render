#include <iostream>
#include "Texture.h"

namespace ginkgo {

	Texture::Texture(const std::string& path, glm::vec4& c)
		: fileName(path), color(c)
	{
		if(fileName.compare(""))
			tid = load();
	}

	Texture::Texture()
	{ 
	
	}

	Texture::~Texture()
	{ 
	
	}

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

	void Texture::bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tid);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}