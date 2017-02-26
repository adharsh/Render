#pragma once

#include <GL/glew.h>

namespace ginkgo {

	class Window;

	class Camera
	{
	private:
		const Window* window;
		glm::mat4 projection;
		glm::mat4 view;
		glm::vec3 cameraPosition;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		GLfloat fov;
		float cameraSpeedSensitivity;
		float mouseRotationSensitivity;
	public:
		Camera(const Window* window, const glm::vec3& camera_position);
		
		void setProjection(const glm::mat4& projection) { this->projection = projection; }
		void setView(const glm::mat4& view) { this->view = view; }
		void setCameraSpeedSensitivity(float cameraSpeedSensitivity) { this->cameraSpeedSensitivity = cameraSpeedSensitivity; }
		void setMouseRotationSensitivity(float mouseSensitivity) { this->mouseRotationSensitivity = mouseSensitivity; }
		void setFOV(float fov) { this->fov= fov; }


		const glm::mat4& getProjection() const { return projection; }
		const glm::mat4& getView() const { return view; }
		const glm::vec3& getCameraPosition() const { return cameraPosition; }
		
		void input(double dt);
		void update(double dt);

	};


}