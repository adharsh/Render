#include <iostream>
#include "Texture.h"


namespace ginkgo{

	Texture::Texture(const std::string path)
		: m_FileName(path)
	{
		m_TID = load();
	}
	
	Texture::Texture()
	{

	}

	Texture::~Texture()
	{

	}

	GLuint Texture::load()
	{
		BYTE* pixels = load_image(m_FileName.c_str(), &m_Width, &m_Height);
		GLenum err;
		err = glGetError();
		if (err != GL_NO_ERROR)
		{
			std::cout << err;
			system("pause");
		}
		GLuint result;
		glGenTextures(1, &result);
		glBindTexture(GL_TEXTURE_2D, result);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
		glBindTexture(GL_TEXTURE_2D, 0);

		err = glGetError();

		if (err != GL_NO_ERROR)
		{
			std::cout << err << std::endl << result << std::endl;
			system("pause");
		}

		delete[] pixels;
		return result;
	}

	void Texture::draw()
	{
		bind();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TID);
		unbind();
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_TID);
	}
	
	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

 }