#pragma once

namespace Game {
	class ChunkManager;
}

#include <vector>
#include <unordered_map>
#include "chunk.h"

namespace Game {

	struct ChunkKeyFuncs
	{
		size_t operator()(const glm::ivec2& k)const
		{
			return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
		}

		bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
		{
			return a.x == b.x && a.y == b.y;
		}
	};

	class ChunkManager {
	public:
		
		void update(glm::vec3 cameraPosition, float deltaTime);
		void render(const glm::mat4& projectionViewMatrix, GLuint mpvShaderLocation);

		//May return null if the given location is within a chunk that hasn't yet been generated
		//or the given id is not registered
		Block* getBlockAt(int worldX, int worldY, int worldZ);
		bool setBlockAt(int worldX, int worldY, int worldZ, uint8_t id);
		Block* castRay(glm::vec3 eye, glm::vec3 direction, int maxDistance = 20);
		bool castRaySetBlock(glm::vec3 eye, glm::vec3 direction, uint8_t blockId, int maxDistance = 20);

	private:
		int m_RenderDistance = 4;
		float m_LastTimeUpdatedChunks = 0;
		std::unordered_map<glm::ivec2, Chunk*, ChunkKeyFuncs, ChunkKeyFuncs> m_Chunks;
		std::unordered_map<glm::ivec2, Chunk*, ChunkKeyFuncs, ChunkKeyFuncs> m_ActiveChunks;

		std::vector<glm::ivec2> m_ReusableVisibleChunkPositions;

		void updateActiveChunks(glm::vec3 cameraPosition);
	};
}