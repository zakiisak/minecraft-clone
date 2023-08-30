#pragma once
#include <GL/glew.h>
#include <stdint.h>
#include <array>
#include <glm/ext/matrix_float4x4.hpp>
#include "block.h"

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 16

namespace Game {
	class Chunk {
	public:
		Chunk(const glm::vec3& offset);
		~Chunk();

		static glm::vec2 getChunkPosition(glm::vec3 worldPosition);
		static glm::vec3 getWorldPosition(glm::ivec2 chunkPosition);

		void loadGraphics();
		void unloadGraphics();
		void build();
		bool isReady();
		void render(const glm::mat4& projectionViewMatrix, GLuint mpvShaderLocation);

		uint8_t getBlockIdOfIndex(int index);
		Block* getBlockAtIndex(int index);
		Block* getBlockAt(int localX, int localY, int localZ);
		uint8_t getBlockIdOfPosition(int localX, int localY, int localZ);
		
		void setBlockAt(int localX, int localY, int localZ, uint8_t blockId);

		glm::vec3 getPositionOffset();

	private:
		glm::vec3 m_ChunkOffset;

		uint8_t* m_Blocks;
		GLuint m_VertexBuffer;
		GLuint m_ColorBuffer;
		GLuint m_TexCoordBuffer;
		GLuint m_IndexBuffer;

		bool m_Initialized = false;
		float m_TimeWhenLastBuilt;
		bool m_Dirty = true;

		float* m_VertexBufferData;
		uint32_t m_VertexBufferIndex = 0; //Count of floats
		GLushort* m_IndexBufferData;
		uint32_t m_IndexBuferIndex;
		float* m_ColorBufferData;
		uint32_t m_ColorBufferIndex = 0; //Count of floats
		float* m_TexCoordBufferData;
		uint32_t m_TexCoordBufferIndex = 0; //Count of floats

		glm::mat4 m_ModelMatrix = glm::mat4(1.0f);
		glm::mat4 m_ReusableMVP;
		glm::vec3 m_ReusableBlockTranslation;
		glm::vec3 m_ReusableFaceColor;
		Block* m_ReusableBlock;

		void addLeftFace();
		void addRightFace();

		void addTopFace();
		void addBottomFace();

		void addFrontFace();
		void addBackFace();

		void addVerticesFromElementIndex(int index, BlockFace face);

		bool isBlockAir(int localX, int localY, int localZ);
		bool isBlockSolid(int localX, int localY, int localZ);
		
	};
}