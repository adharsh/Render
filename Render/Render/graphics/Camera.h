#pragma once

#include <GL\glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Window.h"

namespace ginkgo {

	class Camera
	{
	private:
		const Window& window;
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 model;
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
		void setModel(const glm::mat4& model) { this->model = model; }
		void setCcameraSpeedSensitivity(float cameraSpeedSensitivity) { this->cameraSpeedSensitivity = cameraSpeedSensitivity; }
		void setMouseRotationSensitivity(float mouseSensitivity) { this->mouseRotationSensitivity = mouseRotationSensitivity; }
		void setFOV(const glm::mat4& model) { this->model = model; }


		const glm::mat4& getProjection() const { return projection; }
		const glm::mat4& getView() const { return view; }
		const glm::mat4& getModel() const { return model; }
		const glm::mat4& getTransform() const { return projection * view * model; }
		const glm::vec3& getCameraPosition() const { return cameraPosition; }
		
		void scaleModel(const glm::vec3& scale) { setModel(glm::scale(model, scale)); }
		void translateModel(const glm::vec3& translation) { setModel(glm::translate(model, translation)); }
		void rotateModel(float angleInRadians, const glm::vec3& rotation) { setModel(glm::rotate(model, angleInRadians, rotation)); }

		void input(double dt);
		void update(double dt);

	};


}