#pragma once

#include <string>
#include <GL/glew.h>
#include <FreeImage/FreeImage.h>
#include "../utils/ImageLoad.h"

namespace ginkgo { 

	class Texture
	{
	private:
		std::string m_FileName;
		GLuint m_TID;
		GLsizei m_Width;
		GLsizei m_Height;
	private:
		GLuint load();
	public:
		Texture(const std::string path);
		Texture();
		~Texture();
		void draw();
		void bind() const;
		void unbind() const;
		inline const unsigned int getWidth() const { return m_Width; }
		inline const unsigned int getHeight() const { return m_Height; }
		inline const unsigned int getID() const { return m_TID; }
	};

}

/*
 Textures are used because they are bound
 BatchRenderer2D assumes that textures are constructed before using its m_TextureSlots to reference to OpenGL id's of integers
 renderable2d's only use textures to get their GL id via m_Texture->getID
 */