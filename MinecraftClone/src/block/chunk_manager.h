#pragma once

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

	private:
		int m_RenderDistance = 8;
		float m_LastTimeUpdatedChunks = 0;
		std::unordered_map<glm::ivec2, Chunk*, ChunkKeyFuncs, ChunkKeyFuncs> m_Chunks;
		std::unordered_map<glm::ivec2, Chunk*, ChunkKeyFuncs, ChunkKeyFuncs> m_ActiveChunks;

		std::vector<glm::ivec2> m_ReusableVisibleChunkPositions;

		void updateActiveChunks(glm::vec3 cameraPosition);
	};
}