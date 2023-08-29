#pragma once
#include "graphics/shader.h"
#include "app.h"
#include "graphics/camera.h"
#include "block/chunk.h"
#include "graphics/texture.h"

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
		Texture* textureAtlas;
		Camera camera;

		Chunk* chunk;


		//Temp stuff
		GLuint vertexbuffer;
		GLuint colorbuffer;
	};
}