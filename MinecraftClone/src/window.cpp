#include "window.h"


namespace Core {
	Window::Window(const std::string& title, int width, int height) {
		m_Handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	}

	Window::~Window() {
		glfwDestroyWindow(m_Handle);
	}

	GLFWwindow* Window::getHandle() {
		return m_Handle;
	}

	void Window::assignGLContext() {
		glfwMakeContextCurrent(m_Handle);
	}

	bool Window::shouldClose() {
		return glfwWindowShouldClose(m_Handle);
	}

	void Window::swapBuffers() {
		glfwSwapBuffers(m_Handle);
	}

	bool Window::isInitialized() {
		if (m_Handle)
			return true;
		return false;
	}

	glm::vec2 Window::getSize() {
		if (isInitialized() == false)
			return glm::vec2();
		int width = 0;
		int height = 0;
		glfwGetWindowSize(m_Handle, &width, &height);

		return glm::vec2(width, height);

	}
}