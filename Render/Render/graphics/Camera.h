#pragma once

#include <GL\GL.h>
#include <glm\glm.hpp>

namespace ginkgo {

	class Camera
	{
	private:
		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 model;
		glm::vec3 cameraPosition;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		GLfloat yaw;
		GLfloat pitch;
		GLfloat fov;
		GLfloat lastX;
		GLfloat lastY;
	public:
		Camera(const unsigned int height, const unsigned int width, const glm::vec3& camera_position);
		
		const glm::mat4& getProjection() const { return projection; }
		const glm::mat4& getView() const { return view; }
		const glm::mat4& getModel() const { return model; }
		const glm::mat4& getTransform() const { return projection * view * model; }


		
		void input();

	};


}