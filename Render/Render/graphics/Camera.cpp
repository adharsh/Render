#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\rotate_vector.hpp>
#include "Camera.h"

#include <iostream>

namespace ginkgo {
	Camera::Camera(const Window& win, const glm::vec3& camera_position)
		: window(win), cameraPosition(camera_position)
	{
		yaw = -90.0f;
		pitch = 0.0f;
		fov = 45.0f;//fov 90 or 45?
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		projection = glm::perspective(fov, window.getAspectRatio(), 0.1f, 1000.0f);
		view = glm::lookAt(
			cameraPosition,
			cameraPosition + cameraFront,
			cameraUp);

		cameraSpeedSensitivity = 3.0f;
		mouseRotationSensitivity = 5.0f;
	}

	void Camera::input(double dt)
	{
		GLfloat cameraSpeed = dt * cameraSpeedSensitivity;
		if (window.isKeyPressed(GLFW_KEY_W))
			cameraPosition += cameraSpeed * cameraFront;
		if (window.isKeyPressed(GLFW_KEY_S))
			cameraPosition -= cameraSpeed * cameraFront;
		if (window.isKeyPressed(GLFW_KEY_A))
			cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (window.isKeyPressed(GLFW_KEY_D))
			cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		static bool first = true;
		if (first)
		{
			static double xSave = window.getWidth() / 2.0f;
			static double ySave = window.getHeight() / 2.0f;
			double x, y;
			window.getMousePosition(x, y);
			double dx = x - xSave;
			double dy = y - ySave;

			glm::vec3 look = cameraFront;
			look = glm::rotateY(look, (float)glm::radians(-dx / mouseRotationSensitivity));
			//look = glm::rotateX(look, (float)glm::radians(-dy / mouseRotationSensitivity));
			look = glm::rotate(look, (float)glm::radians(-dy / mouseRotationSensitivity), glm::normalize(glm::cross(look, cameraUp)));

			cameraFront = look;
			xSave = x;
			ySave = y;
		}



		//static double oXS, oYS;
		//static double xS, yS;
		//double yOffset = yS - oYS;
		//oXS = xS;
		//oYS = yS;
		//window.getScrollOffset(xS, yS);
		////std::cout << yOffset << std::endl;


		//if (fov >= 1.0f && fov <= 45.0f)
		//	fov -= yOffset;
		//if (fov <= 1.0f)
		//	fov = 1.0f;
		//if (fov >= 45.0f)
		//	fov = 45.0f;

	}

	void Camera::update(double dt)
	{
		projection = glm::perspective(fov, window.getAspectRatio(), 0.1f, 1000.0f);
		view = glm::lookAt(
			cameraPosition,
			cameraPosition + cameraFront,
			cameraUp);
	}

}