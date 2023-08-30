#include <gl/glew.h>
#include "app.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glm/common.hpp>

static void onWindowResized(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

namespace Core {

	App* App::Instance;

	float App::getTime()
	{
		return (float)glfwGetTime();
	}

	float App::getDeltaTime() {
		return Instance->m_Delta;
	}

	App::App(AppConfig config)
	{
		this->m_Config = config;
	}

	App::~App() {

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		delete m_Window;
		glfwTerminate();
	}

	int App::run() {

		if (!glfwInit())
		{
			std::cerr << "Failed to init GLFW!" << std::endl;
			return -1;
		}
		else
		{
			glfwWindowHint(GLFW_SAMPLES, m_Config.msaaSamples);
			m_Window = new Window(m_Config.title, m_Config.width, m_Config.height);


			if (!m_Window->isInitialized())
			{
				std::cerr << "Failed to init window!" << std::endl;
				return -1;
			}

			Input input(*m_Window);

			m_Window->assignGLContext();

			if (glewInit() != GLEW_OK)
			{
				std::cerr << "Failed to init GLEW!" << std::endl;
				return -1;
			}

			App::Instance = this;
			initImGui();

			create();

			glfwSetFramebufferSizeCallback(m_Window->getHandle(), onWindowResized);

			double time = glfwGetTime();
			double newTime;


			while (m_Window->shouldClose() == false)
			{
				/* Poll for and process events */
				Input::refresh();
				glfwPollEvents();

				update();

				// Start the Dear ImGui frame
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				render();

				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				m_Window->swapBuffers();

				newTime = glfwGetTime();
				m_Delta = newTime - time;
				time = newTime;

			}
		}

		return 0;
	}

	void App::initImGui()
	{

		// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
		const char* glsl_version = "#version 100";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(m_Window->getHandle(), true);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}


	float App::deltaTime() {
		return m_Delta;
	}

	float App::getFps() {
		return 1.0f / glm::max(deltaTime(), 0.0000001f);
	}

	Window* App::getWindow()
	{
		return m_Window;
	}


	void App::update() {

	}

	void App::create()
	{
	}

	void App::render() {
		glClear(GL_COLOR_BUFFER_BIT);
	}
}