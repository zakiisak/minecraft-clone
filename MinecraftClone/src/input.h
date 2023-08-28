#pragma once

#include "window.h"
#include <unordered_map>


namespace Core {
	class Input {
	public:
		Input(Window& inputSourceWindow);


		static void refresh();
		static bool isKeyJustPressed(int key);
		static bool isKeyPressed(int key);
		static bool isMouseButtonPressed(int button);
		static bool isMouseButtonJustPressed(int button);

		static glm::vec2 getMouseDelta();

	private:
		static std::unordered_map<int, bool> m_JustPressedKeys;
		static std::unordered_map<int, bool> m_PressedKeys;
		static std::unordered_map<int, bool> m_JustPressedMouseButtons;
		static std::unordered_map<int, bool> m_PressedMouseButtons;

		static double lastMouseX;
		static double lastMouseY;
		static double mouseDeltaX;
		static double mouseDeltaY;

		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);

		
	};
}