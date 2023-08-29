#include "minecraft_app.h"

#include <stdio.h>
#include <glm/common.hpp>
#include <gl/GL.h>
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include "block/block.h"

namespace Game {

	static Core::AppConfig makeConfig() {
		Core::AppConfig config;
		config.width = 640;
		config.height = 480;
		config.msaaSamples = 8;
		config.title = "Minecraft Clone!";
		
		return config;
	}

	MinecraftApp::MinecraftApp() : Core::App(makeConfig()) {}

	MinecraftApp::~MinecraftApp()
	{
		delete m_TriangleShader;
		delete chunk;
		delete textureAtlas;
		App::~App();
	}

	void MinecraftApp::create()
	{
		m_TriangleShader = new Shader("res/shaders/block/block_vertex.glsl", "res/shaders/block/block_fragment.glsl");

		Block::loadBlocks();

		textureAtlas = new Texture("res/textureAtlas.jpg");

		chunk = new Chunk(glm::vec3(0, 0, 0));
		chunk->initGraphics();
		chunk->build();



		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		//glDisable(GL_CULL_FACE);
		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		camera.position = glm::vec3(0, 0, -10);

		glfwSetInputMode(m_Window->getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	double lastX = 0, lastY = 0;

	void MinecraftApp::update() {
		if (Core::Input::isMouseButtonJustPressed(0))
		{
			glfwSetInputMode(m_Window->getHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		if (Core::Input::isKeyJustPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetInputMode(m_Window->getHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		camera.controlMovement();
		camera.controlPitchAndYaw();

	}

	void MinecraftApp::render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui::Text("position: %f, %f, %f", camera.position.x, camera.position.y, camera.position.z);
		ImGui::Text("pitch: %f, yaw: %f", camera.m_Pitch, camera.m_Yaw);
		ImGui::Text("Fps: %f", getFps());

		m_TriangleShader->enable();
		GLuint matrixID = glGetUniformLocation(m_TriangleShader->getProgram(), "MVP");
		GLuint textureLocation = glGetUniformLocation(m_TriangleShader->getProgram(), "texture");


		glm::mat4 projView = camera.getProjectionMatrix() * camera.getViewMatrix();

		textureAtlas->bind();
		chunk->render(projView, matrixID);
	}
}