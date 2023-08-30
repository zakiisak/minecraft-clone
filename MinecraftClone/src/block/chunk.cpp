#include "chunk.h"
#include <glm/gtx/common.hpp>
#include <stdlib.h>     /* srand, rand */
#include "../app.h"

namespace Game {

	Game::Chunk::Chunk(const glm::vec3& offset)
	{
		m_ChunkOffset = offset;
		//m_Blocks = (uint8_t*) calloc(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE, sizeof(float));
		m_Blocks = new uint8_t[CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE];

		
		for (int i = 0; i < CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE; i++)
		{
			m_Blocks[i] = rand() % 3;
		}


		/*
		for (int x = 1; x < CHUNK_SIZE; x++)
		{
			for (int y = 1; y < CHUNK_HEIGHT; y++)
			{
				for (int z = 1; z < CHUNK_SIZE; z++)
				{
					setBlockAt(x, y, z, 2);
				}
			}
		}*/

		/*
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
		*/
	}

	Game::Chunk::~Chunk()
	{
		unload();
		delete[] m_Blocks;
	}

	glm::vec2 Chunk::getChunkPosition(glm::vec3 worldPosition)
	{
		glm::ivec2 chunkPosition((int) (worldPosition.x / CHUNK_SIZE), (int) (worldPosition.z / CHUNK_SIZE));
		return chunkPosition;
	}

	glm::vec3 Chunk::getWorldPosition(glm::ivec2 chunkPosition)
	{
		return glm::vec3(chunkPosition.x * CHUNK_SIZE, 0, chunkPosition.y * CHUNK_SIZE);
	}

	void Chunk::loadGraphics() {
		if (m_Initialized)
			return;

		m_Initialized = true;

		m_VertexBufferData = new float[CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 12 * 3 * 3]; //2 triangles per face, and there are 6 faces = 12 triangles, with 3 floats each
		m_ColorBufferData = new float[CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 12 * 3 * 3];
		m_TexCoordBufferData = new float[CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE * 12 * 3 * 4];

		glGenBuffers(1, &m_VertexBuffer);
		glGenBuffers(1, &m_IndexBuffer);
		glGenBuffers(1, &m_ColorBuffer);
		glGenBuffers(1, &m_TexCoordBuffer);
	}

	void Chunk::unload()
	{
		if (m_Initialized == false)
			return;

		glDeleteBuffers(1, &m_VertexBuffer);
		glDeleteBuffers(1, &m_IndexBuffer);
		glDeleteBuffers(1, &m_ColorBuffer);
		glDeleteBuffers(1, &m_TexCoordBuffer);
		delete[] m_VertexBufferData;
		delete[] m_ColorBufferData;
		delete[] m_TexCoordBufferData;
		m_Initialized = false;
	}

	constexpr auto BLOCK_SIZE = 0.5f;


	void Chunk::addLeftFace() {
		
		addVerticesFromElementIndex(4, BlockFace::LEFT);
		addVerticesFromElementIndex(0, BlockFace::LEFT);
		addVerticesFromElementIndex(3, BlockFace::LEFT);

		addVerticesFromElementIndex(3, BlockFace::LEFT);
		addVerticesFromElementIndex(7, BlockFace::LEFT);
		addVerticesFromElementIndex(4, BlockFace::LEFT);

		/*
		m_IndexBufferData[m_IndexBuferIndex++] = 4;
		m_IndexBufferData[m_IndexBuferIndex++] = 0;
		m_IndexBufferData[m_IndexBuferIndex++] = 3;

		m_IndexBufferData[m_IndexBuferIndex++] = 3;
		m_IndexBufferData[m_IndexBuferIndex++] = 7;
		m_IndexBufferData[m_IndexBuferIndex++] = 4;
		*/
	}


	void Chunk::addRightFace()
	{

		addVerticesFromElementIndex(1, BlockFace::RIGHT);
		addVerticesFromElementIndex(5, BlockFace::RIGHT);
		addVerticesFromElementIndex(6, BlockFace::RIGHT);

		addVerticesFromElementIndex(6, BlockFace::RIGHT);
		addVerticesFromElementIndex(2, BlockFace::RIGHT);
		addVerticesFromElementIndex(1, BlockFace::RIGHT);

		/*

		m_IndexBufferData[m_IndexBuferIndex++] = 1;
		m_IndexBufferData[m_IndexBuferIndex++] = 5;
		m_IndexBufferData[m_IndexBuferIndex++] = 6;

		m_IndexBufferData[m_IndexBuferIndex++] = 6;
		m_IndexBufferData[m_IndexBuferIndex++] = 2;
		m_IndexBufferData[m_IndexBuferIndex++] = 1;
		*/
	}

	void Chunk::addTopFace()
	{
		addVerticesFromElementIndex(3, BlockFace::TOP);
		addVerticesFromElementIndex(2, BlockFace::TOP);
		addVerticesFromElementIndex(6, BlockFace::TOP);

		addVerticesFromElementIndex(6, BlockFace::TOP);
		addVerticesFromElementIndex(7, BlockFace::TOP);
		addVerticesFromElementIndex(3, BlockFace::TOP);

		/*

		m_IndexBufferData[m_IndexBuferIndex++] = 3;
		m_IndexBufferData[m_IndexBuferIndex++] = 2;
		m_IndexBufferData[m_IndexBuferIndex++] = 6;

		m_IndexBufferData[m_IndexBuferIndex++] = 6;
		m_IndexBufferData[m_IndexBuferIndex++] = 7;
		m_IndexBufferData[m_IndexBuferIndex++] = 3;
		*/
	}

	void Chunk::addBottomFace()
	{
		addVerticesFromElementIndex(4, BlockFace::BOTTOM);
		addVerticesFromElementIndex(5, BlockFace::BOTTOM);
		addVerticesFromElementIndex(1, BlockFace::BOTTOM);

		addVerticesFromElementIndex(1, BlockFace::BOTTOM);
		addVerticesFromElementIndex(0, BlockFace::BOTTOM);
		addVerticesFromElementIndex(4, BlockFace::BOTTOM);


		/*
		m_IndexBufferData[m_IndexBuferIndex++] = 4;
		m_IndexBufferData[m_IndexBuferIndex++] = 5;
		m_IndexBufferData[m_IndexBuferIndex++] = 1;

		m_IndexBufferData[m_IndexBuferIndex++] = 1;
		m_IndexBufferData[m_IndexBuferIndex++] = 0;
		m_IndexBufferData[m_IndexBuferIndex++] = 4;
		*/
	}

	void Chunk::addFrontFace()
	{
		addVerticesFromElementIndex(0, BlockFace::FRONT);
		addVerticesFromElementIndex(1, BlockFace::FRONT);
		addVerticesFromElementIndex(2, BlockFace::FRONT);

		addVerticesFromElementIndex(2, BlockFace::FRONT);
		addVerticesFromElementIndex(3, BlockFace::FRONT);
		addVerticesFromElementIndex(0, BlockFace::FRONT);


		/*
		m_IndexBufferData[m_IndexBuferIndex++] = 0;
		m_IndexBufferData[m_IndexBuferIndex++] = 1;
		m_IndexBufferData[m_IndexBuferIndex++] = 2;

		m_IndexBufferData[m_IndexBuferIndex++] = 2;
		m_IndexBufferData[m_IndexBuferIndex++] = 3;
		m_IndexBufferData[m_IndexBuferIndex++] = 0;
		*/
	}

	void Chunk::addBackFace()
	{
		addVerticesFromElementIndex(7, BlockFace::BACK);
		addVerticesFromElementIndex(6, BlockFace::BACK);
		addVerticesFromElementIndex(5, BlockFace::BACK);

		addVerticesFromElementIndex(5, BlockFace::BACK);
		addVerticesFromElementIndex(4, BlockFace::BACK);
		addVerticesFromElementIndex(7, BlockFace::BACK);

		/*
		m_IndexBufferData[m_IndexBuferIndex++] = 7;
		m_IndexBufferData[m_IndexBuferIndex++] = 6;
		m_IndexBufferData[m_IndexBuferIndex++] = 5;

		m_IndexBufferData[m_IndexBuferIndex++] = 5;
		m_IndexBufferData[m_IndexBuferIndex++] = 4;
		m_IndexBufferData[m_IndexBuferIndex++] = 7;
		*/
	}

	static GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0,  1.0, //0
		 1.0, -1.0,  1.0, //1
		 1.0,  1.0,  1.0, //2
		-1.0,  1.0,  1.0, //3
		// back
		-1.0, -1.0, -1.0, //4
		 1.0, -1.0, -1.0, //5
		 1.0,  1.0, -1.0, //6
		-1.0,  1.0, -1.0  //7
	};



	void Chunk::addVerticesFromElementIndex(int index, BlockFace face)
	{
		m_VertexBufferData[m_VertexBufferIndex++] = cube_vertices[index * 3] * BLOCK_SIZE + m_ReusableBlockTranslation.x;
		m_VertexBufferData[m_VertexBufferIndex++] = cube_vertices[index * 3 + 1] * BLOCK_SIZE + m_ReusableBlockTranslation.y;
		m_VertexBufferData[m_VertexBufferIndex++] = cube_vertices[index * 3 + 2] * BLOCK_SIZE + m_ReusableBlockTranslation.z;

		m_ColorBufferData[m_ColorBufferIndex++] = m_ReusableFaceColor.x;
		m_ColorBufferData[m_ColorBufferIndex++] = m_ReusableFaceColor.y;
		m_ColorBufferData[m_ColorBufferIndex++] = m_ReusableFaceColor.z;
		
		glm::vec4 uv = m_ReusableBlock->getTexCoord(face);
		int indexXAppendage = 0, indexYAppendage = 1;
		if (face == BlockFace::LEFT || face == BlockFace::RIGHT)
		{
			indexXAppendage = 2;
		}
		else if (face == BlockFace::TOP || face == BlockFace::BOTTOM)
		{
			indexYAppendage = 2;
		}
		m_TexCoordBufferData[m_TexCoordBufferIndex++] = uv.x + ((cube_vertices[index * 3 + indexXAppendage] + 1.0f) / 2.0f) * uv.z; //z being the width of the uv
		m_TexCoordBufferData[m_TexCoordBufferIndex++] = uv.y + (1.0f - (cube_vertices[index * 3 + indexYAppendage] + 1.0f) / 2.0f) * uv.w;//W being the height of the uv

	}


	static float randf() {
		return (float)(rand() % 1000) / 1000.0f;
	}

	void Chunk::build()
	{
		if (m_Initialized == false)
		{
			loadGraphics();
		}
		m_TimeWhenLastBuilt = Core::App::getTime();

		m_VertexBufferIndex = 0;
		m_ColorBufferIndex = 0;
		m_TexCoordBufferIndex = 0;

		int x;
		int y;
		int z;
		glm::vec3 offset = glm::vec3();
		bool atLeastOneFacedAdded = false;
		for (x = 0; x < CHUNK_SIZE; x++)
		{
			for (y = 0; y < CHUNK_HEIGHT; y++)
			{
				for (z = 0; z < CHUNK_SIZE; z++)
				{
					m_ReusableBlock = getBlockAt(x, y, z);
					if (m_ReusableBlock == nullptr)
						continue;
					atLeastOneFacedAdded = false;

					m_ReusableFaceColor = glm::vec3(randf(), randf(), randf());
					offset.x = x;
					offset.y = y;
					offset.z = z;
					m_ReusableBlockTranslation = m_ChunkOffset + offset;

					if (isBlockSolid(x, y, z - 1) == false)
					{
						addBackFace();
					}

					if (isBlockSolid(x + 1, y, z) == false)
					{
						addRightFace();
					}

					if (isBlockSolid(x, y, z + 1) == false)
					{
						addFrontFace();
					}

					if (isBlockSolid(x - 1, y, z) == false)
					{
						addLeftFace();
					}

					if (isBlockSolid(x, y - 1, z) == false)
					{
						addBottomFace();
					}

					if (isBlockSolid(x, y + 1, z) == false)
					{
						addTopFace();
					}
				}
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_VertexBufferIndex, m_VertexBufferData, GL_STATIC_DRAW);

		/*
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_IndexBuferIndex, m_IndexBufferData, GL_STATIC_DRAW);
		*/

		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_ColorBufferIndex, m_ColorBufferData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_TexCoordBufferIndex, m_TexCoordBufferData, GL_STATIC_DRAW);
	}

	bool Chunk::isLoaded()
	{
		return m_Initialized;
	}

	void Chunk::render(const glm::mat4& projectionViewMatrix, GLuint mpvShaderLocation)
	{
		m_ReusableMVP = projectionViewMatrix * m_ModelMatrix; // Remember, matrix multiplication is the other way around
		glUniformMatrix4fv(mpvShaderLocation, 1, GL_FALSE, &m_ReusableMVP[0][0]);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		
		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 3rd attribute buffer : colors
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordBuffer);
		glVertexAttribPointer(
			2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		

		glDrawArrays(GL_TRIANGLES, 0, m_VertexBufferIndex / 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);

		/*
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		//int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		glDrawElements(GL_TRIANGLES, m_IndexBuferIndex, GL_UNSIGNED_SHORT, 0);
		glDisableVertexAttribArray(0);
		*/

	}

	uint8_t Chunk::getBlockIdOfIndex(int index)
	{
		if (index < 0 || index >= CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE)
			return 0;
		return m_Blocks[index];
	}

	Block* Chunk::getBlockAtIndex(int index)
	{
		if (index < 0 || index >= CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE)
			return nullptr;
		return Block::blocks[m_Blocks[index]];
	}

	Block* Chunk::getBlockAt(int localX, int localY, int localZ)
	{
		uint8_t id = getBlockIdOfPosition(localX, localY, localZ);
		if (id == 0)
			return nullptr;
		return Block::blocks[id];
	}

	uint8_t Chunk::getBlockIdOfPosition(int localX, int localY, int localZ)
	{
		int index = (localX * CHUNK_SIZE * CHUNK_HEIGHT) + (localY * CHUNK_HEIGHT) + CHUNK_SIZE;
		if (index < 0 || index >= CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE)
			return 0;
		return m_Blocks[index];
	}

	void Chunk::setBlockAt(int localX, int localY, int localZ, uint8_t blockId)
	{
		int index = (localX * CHUNK_SIZE * CHUNK_HEIGHT) + (localY * CHUNK_HEIGHT) + CHUNK_SIZE;
		if (index < 0 || index >= CHUNK_SIZE * CHUNK_HEIGHT * CHUNK_SIZE)
			return;
		m_Blocks[index] = blockId;
		m_Dirty = true;
	}

	glm::vec3 Chunk::getPositionOffset()
	{
		return m_ChunkOffset;
	}

	bool Chunk::isBlockAir(int localX, int localY, int localZ)
	{
		return Block::blocks[getBlockIdOfPosition(localX, localY, localZ)] != nullptr;
	}

	bool Chunk::isBlockSolid(int localX, int localY, int localZ)
	{
		Block* block = getBlockAt(localX, localY, localZ);
		if (block == nullptr)
			return false;
		return block->isOpaque();
	}

}
