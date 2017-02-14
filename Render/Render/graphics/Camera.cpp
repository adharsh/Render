#include "Camera.h"

namespace ginkgo {
	Camera::Camera(const unsigned int height, const unsigned int width, const glm::vec3& camera_position)
		: cameraPosition(camera_position), lastX(width / 2.0f), lastY(height / 2.0f)
	{
		yaw = -90.0f;
		pitch = 0.0f;
		fov = 45.0f;
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}


}