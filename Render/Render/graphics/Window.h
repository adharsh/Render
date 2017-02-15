#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace ginkgo {

		class Window
		{
		public:
			static const int MAX_KEYS = 1024;
			static const int MAX_BUTTONS = 32;
		private:
			const char *title;
			unsigned int width, height;
			GLFWwindow *window;
			bool keys[MAX_KEYS];
			bool mouseButtons[MAX_BUTTONS];
			double mx;
			double my;
			double s_xoffset;
			double s_yoffset;
			glm::vec4 clear_color;
			bool isFullScreen;
		public:
			Window(const char *name, int width, int height, const glm::vec4& clear_color, bool wantFullScreen = false);
			Window() {
				Window("Render", 800, 600, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			}
			~Window();
			void update() const;
			bool closed() const;
			void clear() const;

			unsigned int getWidth() const { return width; }
			unsigned int getHeight() const { return height; }
			float getAspectRatio() const{ return (float)width / (float)height; }

			void setClearColor(const glm::vec4& color) { clear_color = color; }

			bool isKeyPressed(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;
			void getScrollOffset(double& xoffset, double& yoffset) const;

			void disableMouseCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); }
			void showMouseCursor() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
		private:
			bool init();

			friend void window_resize(GLFWwindow* window, int width, int height);
			friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
			friend void scroll_callback(GLFWwindow* window, double xpos, double ypos);

		};



	}
