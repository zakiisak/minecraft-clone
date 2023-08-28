#pragma once
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/vec2.hpp>

namespace Core {
	class Window {
	public:
		Window(const std::string& title, int width, int height);
		~Window();

		void assignGLContext();
		glm::vec2 getSize();

		bool shouldClose();
		void swapBuffers();

		bool isInitialized();

		GLFWwindow* getHandle();

	private:
		GLFWwindow* m_Handle;

	};
}
