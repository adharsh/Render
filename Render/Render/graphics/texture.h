#pragma once

#include <string>
#include <GL/glew.h>
#include <FreeImage/FreeImage.h>

#include "../utils/FileUtils.h"

namespace ginkgo {

	class Texture
	{
	private:
		std::string fileName;
		GLuint tid;
		GLsizei width;
		GLsizei height;
		glm::vec4 color;
	private:
		GLuint load();
	public:
		Texture(const std::string& path, glm::vec4& color);
		Texture();
		~Texture();
		void bind();
		void unbind();
		inline const bool hasImage() const { return fileName.compare(""); }
		inline const unsigned int getWidth() const { return width; }
		inline const unsigned int getHeight() const { return height; }
		inline const unsigned int getID() const { return tid; }
		inline const glm::vec4& getColor() { return color; }
		inline void setColor(glm::vec4& color) { this->color = color; }
	};

}

/*
Textures are used because they are bound
BatchRenderer2D assumes that textures are constructed before using its m_TextureSlots to reference to OpenGL id's of integers
renderable2d's only use textures to get their GL id via m_Texture->getID
*/