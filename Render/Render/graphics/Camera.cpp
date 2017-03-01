#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include "Window.h"

#include "Camera.h"

namespace ginkgo {
	Camera::Camera(const Window* win, const glm::vec3& camera_position)
		: window(win), cameraPosition(camera_position)
	{
		fov = 45.0f;//fov 90 or 45?
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		projection = glm::perspective(fov, window->getAspectRatio(), 0.1f, 1000.0f);
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
		if (window->isKeyPressed(GLFW_KEY_W))
			cameraPosition += cameraSpeed * cameraFront;
		if (window->isKeyPressed(GLFW_KEY_S))
			cameraPosition -= cameraSpeed * cameraFront;
		if (window->isKeyPressed(GLFW_KEY_A))
			cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (window->isKeyPressed(GLFW_KEY_D))
			cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

		static unsigned int width = window->getWidth();
		static unsigned int height = window->getHeight();
		static double xSave = width / 2.0f;
		static double ySave = height / 2.0f;
		if (width != window->getWidth() || height != window->getHeight())
		{
			width = window->getWidth();
			height = window->getHeight();
			window->setMousePosition(window->getWidth() / 2.0f, window->getHeight() / 2.0f);
			xSave = window->getWidth() / 2.0f;
			ySave = window->getHeight() / 2.0f;
		}
		double x, y;
		window->getMousePosition(x, y);
		double dx = x - xSave;
		double dy = y - ySave;

		glm::vec3 look = cameraFront;
		
		//float rotateOnYAxisAngle = (float)-dx / mouseRotationSensitivity * 800.0f / window->getWidth();
		//float rotateAngle = (float)(-dy / mouseRotationSensitivity * 600.0f / window->getHeight());
		//
		//rotateOnYAxisAngle = fmod(rotateOnYAxisAngle, 360.0f);
		//float limitAngle = 360.0f;
		//rotateOnYAxisAngle = (rotateOnYAxisAngle > limitAngle) ?
		//	limitAngle :
		//	(rotateOnYAxisAngle < -limitAngle) ? -limitAngle : rotateOnYAxisAngle;
		//
		//rotateAngle = fmod(rotateAngle, 360.0f);
		//rotateAngle = (rotateAngle > limitAngle) ?
		//	limitAngle :
		//	(rotateAngle < -limitAngle) ? -limitAngle : rotateAngle;
		//
		//look = glm::rotateY(look, (float)glm::radians(rotateOnYAxisAngle));
		//look = glm::rotate(look, (float)glm::radians((float)(rotateAngle)), glm::normalize(glm::cross(look, cameraUp)));

		look = glm::rotateY(look, (float)glm::radians((float)-dx / mouseRotationSensitivity * 800.0f / window->getWidth()));
		look = glm::rotate(look, (float)glm::radians((float)((float)(-dy / mouseRotationSensitivity * 600.0f / window->getHeight()))), glm::normalize(glm::cross(look, cameraUp)));
		//look = glm::rotateX(look, (float)glm::radians((float)-dy / mouseRotationSensitivity * 600.0f / window->getHeight()));

		cameraFront = look;
		xSave = x;
		ySave = y;

		//static double xSave = 0;
		//static double ySave = 0;
		//double x, y;
		//window->getMousePosition(x, y);
		//static bool first = true;
		//if (!first)
		//{
		//	double dx = x - xSave;
		//	double dy = y - ySave;

		//	glm::vec3 look = cameraFront;

		//	look = glm::rotateY(look, (float)glm::radians(-dx / mouseRotationSensitivity));
		//	look = glm::rotate(look, (float)glm::radians(-dy / mouseRotationSensitivity), glm::normalize(glm::cross(look, cameraUp)));

		//	cameraFront = look;
		//}
		//first = false;
		//xSave = x;
		//ySave = y;


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
		projection = glm::perspective(fov, window->getAspectRatio(), 0.1f, 1000.0f);
		view = glm::lookAt(
			cameraPosition,
			cameraPosition + cameraFront,
			cameraUp);
	}

}