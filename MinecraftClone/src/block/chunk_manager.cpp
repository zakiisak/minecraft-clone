#include "chunk_manager.h"
#include "../app.h"

namespace Game {
	void ChunkManager::update(glm::vec3 cameraPosition, float deltaTime)
	{
		if (Core::App::getTime() - m_LastTimeUpdatedChunks > 0.5f)
		{
			updateActiveChunks(cameraPosition);
		}
	}

	void ChunkManager::render(const glm::mat4& projectionViewMatrix, GLuint mpvShaderLocation)
	{
		for (auto pair : m_ActiveChunks)
		{
			pair.second->render(projectionViewMatrix, mpvShaderLocation);
		}
	}

	void ChunkManager::updateActiveChunks(glm::vec3 cameraPosition)
	{
		glm::ivec2 chunkPosition = Chunk::getChunkPosition(cameraPosition + glm::vec3(CHUNK_SIZE / 2, 0, CHUNK_SIZE / 2));
		int startChunkX = chunkPosition.x - m_RenderDistance / 2;
		int startChunkZ = chunkPosition.y - m_RenderDistance / 2;
		int endChunkX = chunkPosition.x + m_RenderDistance / 2 - 1;
		int endChunkZ = chunkPosition.y + m_RenderDistance / 2;

		for (auto pair : m_ActiveChunks)
		{
			int x = pair.first.x;
			int z = pair.first.y;
			if (x < startChunkX || x > endChunkX || z < startChunkZ || z > endChunkZ)
			{
				if (pair.second->isLoaded())
					pair.second->unload();
			}
		}
		m_ActiveChunks.clear();

		m_ReusableVisibleChunkPositions.clear();


		for (int x = startChunkX; x < endChunkX + 1; x++)
		{
			for (int z = startChunkZ; z < endChunkZ; z++)
			{
				glm::ivec2 chunkKey = glm::ivec2(x, z);
				Chunk* chunk;
				if (m_Chunks.find(chunkKey) == m_Chunks.end())
				{
					chunk = new Chunk(Chunk::getWorldPosition(chunkKey));
					chunk->build();
					m_Chunks[chunkKey] = chunk;
				}
				else
				{
					chunk = m_Chunks[chunkKey];
					if (chunk->isLoaded() == false)
						chunk->build();
				}
				m_ActiveChunks[chunkKey] = chunk;
			}
		}

	}

}
