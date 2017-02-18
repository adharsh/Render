#pragma once

#include <GL\glew.h>

#include "Window.h"

namespace ginkgo {

	class Camera
	{
	private:
		const Window& window;
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 mvp;
		glm::vec3 cameraPosition;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		GLfloat yaw;
		GLfloat pitch;
		GLfloat fov;
		float cameraSpeedSensitivity;
		float mouseRotationSensitivity;
	public:
		Camera(const Window& window, const glm::vec3& camera_position);
		
		void setProjection(const glm::mat4& projection) { this->projection = projection; }
		void setView(const glm::mat4& view) { this->view = view; }
		void setCcameraSpeedSensitivity(float cameraSpeedSensitivity) { this->cameraSpeedSensitivity = cameraSpeedSensitivity; }
		void setMouseRotationSensitivity(float mouseSensitivity) { this->mouseRotationSensitivity = mouseRotationSensitivity; }
		void setFOV(float fov) { this->fov= fov; }


		const glm::mat4& getProjection() const { return projection; }
		const glm::mat4& getView() const { return view; }
		const glm::mat4& getMVP(const glm::mat4& model) { mvp = projection * view * model; return mvp; }
		const glm::vec3& getCameraPosition() const { return cameraPosition; }
		
		void input(double dt);
		void update(double dt);

	};


}