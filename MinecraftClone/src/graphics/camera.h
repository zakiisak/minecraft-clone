#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace Game {
	class Camera {
	public:
		Camera();
		glm::vec3 position = glm::vec3(0);
		glm::vec3 look = glm::vec3(0);
		float fov = 67;
		float near = 0.1f;
		float far = 1000.0f;
		float m_Pitch = 0;
		float m_Yaw = 0;

		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();

		glm::vec3 right();

		void setLookFromPitchAndYaw(float pitch, float yaw);
		void controlMovement();
		void controlPitchAndYaw();
	private:

	};
}