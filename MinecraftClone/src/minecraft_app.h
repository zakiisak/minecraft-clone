#pragma once
#include "graphics/shader.h"
#include "app.h"
#include "graphics/camera.h"
#include "block/chunk.h"
#include "graphics/texture.h"
#include "block/chunk_manager.h"

namespace Game {
	class MinecraftApp : public Core::App {
	public:
		MinecraftApp();
		~MinecraftApp();
		void create() override;
		void update() override;
		void render() override;

		void ssaoPass();

	private:
		Shader* m_Shader;
		Shader* m_SSAOGeometryShader;
		Texture* textureAtlas;
		Camera camera;

		ChunkManager chunkManager;
	};
}