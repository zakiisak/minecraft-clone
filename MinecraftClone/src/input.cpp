#include "input.h"
#include <GLFW/glfw3.h>

namespace Core {

	std::unordered_map<int, bool> Input::m_JustPressedKeys;
	std::unordered_map<int, bool> Input::m_PressedKeys;
	std::unordered_map<int, bool> Input::m_JustPressedMouseButtons;
	std::unordered_map<int, bool> Input::m_PressedMouseButtons;

	double Input::lastMouseX;
	double Input::lastMouseY;
	double Input::mouseDeltaX;
	double Input::mouseDeltaY;

	Input::Input(Window &window) {
		glfwSetKeyCallback(window.getHandle(), this->keyCallback);
		glfwSetMouseButtonCallback(window.getHandle(), this->mouseButtonCallback);
		glfwSetCursorPosCallback(window.getHandle(), this->mousePosCallback);
	}

	bool Input::isKeyJustPressed(int key) {
		return m_JustPressedKeys[key];
	}

	bool Input::isKeyPressed(int key) {
		return m_PressedKeys[key];
	}

	bool Input::isMouseButtonPressed(int button)
	{
		return m_PressedMouseButtons[button];
	}

	bool Input::isMouseButtonJustPressed(int button)
	{
		return m_JustPressedMouseButtons[button];
	}

	glm::vec2 Input::getMouseDelta()
	{
		return glm::vec2(mouseDeltaX, mouseDeltaY);
	}

	void Input::refresh() {
		m_JustPressedKeys.clear();
		m_JustPressedMouseButtons.clear();
		mouseDeltaX = 0;
		mouseDeltaY = 0;
	}

	void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action != GLFW_RELEASE)
		{
			m_JustPressedKeys[key] = true;
			m_PressedKeys[key] = true;
		}
		else m_PressedKeys[key] = false;
	}

	void Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action != GLFW_RELEASE)
		{
			m_JustPressedMouseButtons[button] = true;
			m_PressedMouseButtons[button] = true;
		}
		else m_PressedMouseButtons[button] = false;
	}
	void Input::mousePosCallback(GLFWwindow* window, double xpos, double ypos)
	{
		mouseDeltaX = xpos - lastMouseX;
		mouseDeltaY = ypos - lastMouseY;

		lastMouseX = xpos;
		lastMouseY = ypos;
	}
}