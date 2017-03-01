#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>

#include "Window.h"

#include "Camera.h"

namespace ginkgo {
	Camera::Camera(const Window* win, const glm::vec3& camera_position)
		: window(win), cameraPosition(camera_position)
	{
		fov = 45.0f;//fov 90 or 45?
	/*	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);*/

		projection = glm::perspective(fov, window->getAspectRatio(), 0.1f, 1000.0f);

		glm::quat pitch = glm::angleAxis(0.f, glm::vec3(1, 0, 0));
		glm::quat yaw = glm::angleAxis(0.f, glm::vec3(0, 1, 0));

		cameraRotation = glm::normalize(pitch * yaw);
		view = glm::toMat4(cameraRotation);

		cameraSpeedSensitivity = 3.0f; //3.0f
		mouseRotationSensitivity = 200.f; //5.0f

		window->disableMouseCursor();
		window->setMousePosition(window->getWidth() / 2.0f, window->getHeight() / 2.0f);

		xSave = window->getWidth() / 2.0;
		ySave = window->getHeight() / 2.0;
	}

	void Camera::input(double dt)
	{
		GLfloat cameraSpeed = dt * cameraSpeedSensitivity;
		glm::vec3 r;
		glm::vec3 f;

		r.x = view[0][0];
		r.y = view[1][0];
		r.z = view[2][0];

		f.x = -view[0][2];
		f.y = -view[1][2];
		f.z = -view[2][2];

		r = glm::normalize(r);
		f = glm::normalize(f);

		//std::cout << r.x << " " << r.y << " " << r.z << "::" << f.x << " " << f.y << " " << f.z << std::endl;

		if (window->isKeyPressed(GLFW_KEY_W))
			cameraPosition += cameraSpeed * f;
		if (window->isKeyPressed(GLFW_KEY_S))
			cameraPosition -= cameraSpeed * f;
		if (window->isKeyPressed(GLFW_KEY_A))
			cameraPosition -= r * cameraSpeed;
		if (window->isKeyPressed(GLFW_KEY_D))
			cameraPosition += r * cameraSpeed;

		static bool first = true;
		double x, y;
		window->getMousePosition(x, y);


		static float _pitch = 0;
		static float _yaw = 0;

	/*	if (width != window->getWidth() || height != window->getHeight())
		{
			width = window->getWidth();
			height = window->getHeight();
			window->setMousePosition(window->getWidth() / 2.0f, window->getHeight() / 2.0f);
			xSave = window->getWidth() / 2.0f;
			ySave = window->getHeight() / 2.0f;
			return;
		}*/
		

		double dx = x - xSave;
		double dy = y - ySave;

		if (x == 0 || y == 0)
		{
			return;
		}

		if (x != 0 && y != 0 && xSave == 0 && ySave == 0 && first)
		{
			first = false;
			xSave = x;
			ySave = y;
			dx = 0;
			dy = 0;
		}

		_pitch += (dy / mouseRotationSensitivity);
		_yaw += (dx / mouseRotationSensitivity);

		//window->setMousePosition(window->getWidth() / 2.0f, window->getHeight() / 2.0f);


		glm::quat pitch = glm::angleAxis(_pitch, glm::vec3(1, 0, 0));
		glm::quat yaw = glm::angleAxis(_yaw, glm::vec3(0, 1, 0));

		cameraRotation = glm::normalize(pitch * yaw);

		/*glm::vec3 look = cameraFront;
		glm::vec3 side = glm::normalize(glm::cross(look, cameraUp));
		look = glm::rotateY(look, (float)glm::radians((float)-dx / mouseRotationSensitivity * 800.0f / window->getWidth()));
		
		look = glm::rotate(look, (float)glm::radians((float)((float)(-dy / mouseRotationSensitivity * 600.0f / window->getHeight()))), side); //gimbal lock
		*/
		//std::cout << print.x << " " << print.y << " " << print.z << std::endl;
		//look = glm::rotateX(look, (float)glm::radians((float)-dy / mouseRotationSensitivity * 600.0f / window->getHeight()));

		//cameraFront = look;
		xSave = x;
		ySave = y;

	}

	void Camera::update(double dt)
	{
		projection = glm::perspective(fov, window->getAspectRatio(), 0.1f, 1000.0f);
		view = glm::toMat4(cameraRotation);
		/*
		lookat 3 vecs = one vec -> view
		*/
	}

}