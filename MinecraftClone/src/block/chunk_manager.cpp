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
		m_LastUsedChunks.clear();
		for (auto pair : m_ActiveChunks)
		{
			m_LastUsedChunks[pair.first] = pair.second;
		}

		m_ActiveChunks.clear();
		m_ReusableVisibleChunkPositions.clear();

		glm::ivec2 chunkPosition = Chunk::getChunkPosition(cameraPosition);

		for (int x = chunkPosition.x - m_RenderDistance / 2; x < chunkPosition.x + m_RenderDistance / 2; x++)
		{
			for (int z = chunkPosition.y - m_RenderDistance / 2; z < chunkPosition.y + m_RenderDistance / 2; z++)
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
					if (chunk->isReady() == false)
						chunk->build();
				}
				m_ActiveChunks[chunkKey] = chunk;
			}
		}

		for (auto pair : m_LastUsedChunks)
		{
			if (m_ActiveChunks.find(pair.first) == m_ActiveChunks.end())
			{
				pair.second->unloadGraphics();
			}
		}


	}

}
