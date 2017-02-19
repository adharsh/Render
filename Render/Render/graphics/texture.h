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
		float specularIntensity;
		float specularPower;
		static std::string whitepixelfilepath;
	private:
		GLuint load(); //images -> no alpha, remove transparency in Gimp Layer->Transparency->Remove Alpha Channel
	public:
		Texture(const glm::vec4& color, const std::string& path = whitepixelfilepath);
		Texture(const glm::vec4& color, float specularIntensity, float specularExponent, const std::string& path = whitepixelfilepath);
		~Texture();
		const unsigned int getWidth() const { return width; }
		const unsigned int getHeight() const { return height; }
		const GLuint getID() const { return tid; }
		const glm::vec4& getColor() const { return color; }
		const float getSpecularIntensity() const { return specularIntensity; }
		const float getSpecularPower() const { return specularPower; }

		void setColor(const glm::vec4& color) { this->color = color; }

		const void setSpecularIntensity() { this->specularIntensity = specularIntensity; }
		const void setSpecularPower() { this->specularPower = specularPower; }

		static void setWhitePixelFilePath(const std::string& filepath) { whitepixelfilepath = filepath; }
	};

}

/*
Textures are used because they are bound
BatchRenderer2D assumes that textures are constructed before using its m_TextureSlots to reference to OpenGL id's of integers
renderable2d's only use textures to get their GL id via m_Texture->getID
*/