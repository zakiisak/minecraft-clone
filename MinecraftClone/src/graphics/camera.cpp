#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../app.h"

namespace Game {

	Camera::Camera()
	{
	}

	glm::mat4 Camera::getProjectionMatrix() {

		glm::vec2 windowSize = Core::App::Instance->getWindow()->getSize();
		return glm::perspective(glm::radians(fov), (float)windowSize.x / (float)windowSize.y, near, far);
	}
	glm::mat4 Camera::getViewMatrix()
	{
		return glm::lookAt(position, position + look, glm::vec3(0, 1, 0));
	}
	glm::vec3 Camera::right()
	{
		glm::vec3 crossed = glm::cross(look, glm::vec3(0, 1, 0));
		return glm::normalize(crossed);
	}

	void Camera::setLookFromPitchAndYaw(float pitch, float yaw)
	{
		pitch = glm::radians(pitch);
		yaw = glm::radians(yaw);
		look.x = glm::cos(pitch) * glm::cos(yaw);
		look.y = glm::sin(pitch);
		look.z = glm::cos(pitch) * glm::sin(yaw);
		look = glm::normalize(look);
	}

	void Camera::controlMovement()
	{
		float speed = 4.0f;

		if (Core::Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
		{
			speed *= 4;
		}
		glm::vec3 ms(0);
		if (Core::Input::isKeyPressed(GLFW_KEY_W))
		{
			ms += look * speed;
		}
		if (Core::Input::isKeyPressed(GLFW_KEY_S))
		{
			ms -= look * speed;
		}

		if (Core::Input::isKeyPressed(GLFW_KEY_A))
		{
			ms -= right() * speed;
		}
		if (Core::Input::isKeyPressed(GLFW_KEY_D))
		{
			ms += right() * speed;
		}

		float delta = Core::App::Instance->deltaTime();
		position += ms * delta;
	}

	void Camera::controlPitchAndYaw()
	{
		glm::vec2 mouseDelta = Core::Input::getMouseDelta();

		const float sensitivity = 16.0f;
		float delta = Core::App::Instance->deltaTime();
		m_Yaw += mouseDelta.x * delta * sensitivity;
		m_Pitch -= mouseDelta.y * delta * sensitivity;

		if (m_Pitch < -89.99f)
			m_Pitch = -89.99f;
		if (m_Pitch > 89.99f)
			m_Pitch = 89.99f;

		setLookFromPitchAndYaw(m_Pitch, m_Yaw);
	}
}

