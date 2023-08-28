#pragma once
#include "graphics/shader.h"
#include "app.h"
#include "graphics/camera.h"

namespace Game {
	class MinecraftApp : public Core::App {
	public:
		MinecraftApp();
		~MinecraftApp();
		void create() override;
		void update() override;
		void render() override;

	private:
		Shader* m_TriangleShader;
		Camera camera;


		//Temp stuff
		GLuint vertexbuffer;
		GLuint colorbuffer;
	};
}