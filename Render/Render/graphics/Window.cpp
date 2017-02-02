#include "window.h"
#include <iostream>

namespace ginkgo {
		Window::Window(const char *name, int width, int height, glm::vec4& clear_color)
		{
			this->title = name;
			this->width = width;
			this->height = height;
			this->clear_color = clear_color;

			if (!init())
				glfwTerminate();

			for (int i = 0; i < MAX_KEYS; i++)
				keys[i] = false;

			for (int i = 0; i < MAX_BUTTONS; i++)
				mouseButtons[i] = false;
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}

			window = glfwCreateWindow(width, height, title, NULL, NULL);
			if (!window)
			{
				glfwTerminate();
				std::cout << "Failed to return a window!" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(window);
			glfwSetWindowUserPointer(window, this);
			glfwSetFramebufferSizeCallback(window, window_resize);
			glfwSetKeyCallback(window, key_callback);
			glfwSetMouseButtonCallback(window, mouse_button_callback);
			glfwSetCursorPosCallback(window, cursor_position_callback);
			glfwSetScrollCallback(window, scroll_callback);

			//optimize for more than 60 fps
			glfwSwapInterval(0);

			//************************************************
			//glew must be initialized AFTER glfw makes context 
			//************************************************

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

			/**********Other Settings**********/
			//glFrontFace(GL_CW);	//Drawing front face in Clockwise 
			//glCullFace(GL_BACK); //Not drawing back face
			//glEnable(GL_CULL_FACE);	//Not drawing unnecessary front and back stuff
			glEnable(GL_DEPTH_TEST); //Z component for depth
			glDepthFunc(GL_LESS);
			//Depth clamp for later
			//glEnable(GL_FRAMEBUFFER_SRGB); //More gamma correction, all other colors are already exponential, it does it for us
			//Wireframe
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			return true;
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			if (keycode >= MAX_KEYS)
				return false;

			return keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			if (button >= MAX_BUTTONS)
				return false;

			return mouseButtons[button];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = mx;
			y = my;
		}

		void Window::getScrollOffset(double& xvalue, double& yvalue) const
		{
			xvalue = s_xoffset;
			yvalue = s_yoffset;
		}


		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		}

		void Window::update()
		{
			glfwPollEvents();

	//		glfwGetFramebufferSize(Window, &Width, &Height);
			glfwSwapBuffers(window);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(window) == 1;
		}

		void window_resize(GLFWwindow *window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window* win = (Window *)glfwGetWindowUserPointer(window);
			win->width = width;
			win->height = height;
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window *)glfwGetWindowUserPointer(window);
			win->keys[key] = (action != GLFW_RELEASE);
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window *)glfwGetWindowUserPointer(window);
			win->mouseButtons[button] = (action != GLFW_RELEASE);
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window *)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}

		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
		{
			Window* win = (Window *)glfwGetWindowUserPointer(window);
			win->s_xoffset = xoffset;
			win->s_yoffset = yoffset;
		}


}