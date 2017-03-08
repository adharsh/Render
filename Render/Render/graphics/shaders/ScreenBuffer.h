#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"

namespace ginkgo {

	class ScreenBuffer : public Shader
	{
	private:
		GLuint FBO; //frame buffer object
		GLuint RBO; //render buffer object
		GLuint textureID; //texture color buffer
		GLuint quadVAO; //rectangle
		GLuint quadVBO; //rectangle
		glm::vec4 clear_color;
	public:
		ScreenBuffer(unsigned int screenWidth, unsigned int screenHeight, glm::vec4 clear_color, bool depth, bool stencil);
		~ScreenBuffer();

		void draw() const;

		void bindBuffer() const;
		static void bindDefaultBuffer();

		//make bind methods overaload Shader methods for everything that's already done

		static void clearColor(const glm::vec4& clear_color);
		static void clearBuffer(bool colorBuffer, bool depthBuffer, bool stencilBuffer);
		
		static void enableDepthTest() { glEnable(GL_DEPTH_TEST); }
		static void enableStencilTest() { glEnable(GL_STENCIL_TEST); }
		static void disableDepthTest() { glDisable(GL_DEPTH_TEST); }
		static void disableStencilTest() { glDisable(GL_STENCIL_TEST); }
		void bindShader() const { bind(); }
		void unbindShader() const { unbind(); }
	};

}