#include "chunk.h"
#include <glm/gtx/common.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

namespace Game {

	Game::Chunk::Chunk(const glm::vec3& offset)
	{
		srand(time(NULL));

		m_ChunkOffset = offset;
		//m_Blocks = (uint8_t*) calloc(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE, sizeof(float));
		m_Blocks = new uint8_t[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

		for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE; i++)
		{
			m_Blocks[i] = 0;
		}

		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				for (int z = 0; z < 4; z++)
				{
					setBlockAt(x, y, z, 1);
				}
			}
		}

		setBlockAt(0, 0, 0, 1);
		setBlockAt(0, 1, 0, 1);

		//Randomize the chunk with data

	}

	Game::Chunk::~Chunk()
	{
		delete m_Blocks;
	}

	void Chunk::initGraphics() {

		m_VertexBufferData = new float[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 12 * 3 * 3]; //2 triangles per face, and there are 6 faces = 12 triangles, with 3 floats each
		m_ColorBufferData = new float[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 12 * 3 * 3];

		glGenBuffers(1, &m_VertexBuffer);
		glGenBuffers(1, &m_IndexBuffer);
		glGenBuffers(1, &m_ColorBuffer);
	}

	constexpr auto BLOCK_SIZE = 0.5f;


	void Chunk::addLeftFace() {
		
		addVerticesFromElementIndex(4);
		addVerticesFromElementIndex(0);
		addVerticesFromElementIndex(3);

		addVerticesFromElementIndex(3);
		addVerticesFromElementIndex(7);
		addVerticesFromElementIndex(4);

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

		addVerticesFromElementIndex(1);
		addVerticesFromElementIndex(5);
		addVerticesFromElementIndex(6);

		addVerticesFromElementIndex(6);
		addVerticesFromElementIndex(2);
		addVerticesFromElementIndex(1);

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
		addVerticesFromElementIndex(3);
		addVerticesFromElementIndex(2);
		addVerticesFromElementIndex(6);

		addVerticesFromElementIndex(6);
		addVerticesFromElementIndex(7);
		addVerticesFromElementIndex(3);

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
		addVerticesFromElementIndex(4);
		addVerticesFromElementIndex(5);
		addVerticesFromElementIndex(1);

		addVerticesFromElementIndex(1);
		addVerticesFromElementIndex(0);
		addVerticesFromElementIndex(4);


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
		addVerticesFromElementIndex(0);
		addVerticesFromElementIndex(1);
		addVerticesFromElementIndex(2);

		addVerticesFromElementIndex(2);
		addVerticesFromElementIndex(3);
		addVerticesFromElementIndex(0);


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
		addVerticesFromElementIndex(7);
		addVerticesFromElementIndex(6);
		addVerticesFromElementIndex(5);

		addVerticesFromElementIndex(5);
		addVerticesFromElementIndex(4);
		addVerticesFromElementIndex(7);

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

	void Chunk::addVerticesFromElementIndex(int index)
	{
		m_VertexBufferData[m_VertexBufferIndex++] = cube_vertices[index * 3] * BLOCK_SIZE + m_ReusableBlockTranslation.x;
		m_VertexBufferData[m_VertexBufferIndex++] = cube_vertices[index * 3 + 1] * BLOCK_SIZE + m_ReusableBlockTranslation.y;
		m_VertexBufferData[m_VertexBufferIndex++] = cube_vertices[index * 3 + 2] * BLOCK_SIZE + m_ReusableBlockTranslation.z;

		m_ColorBufferData[m_ColorBufferIndex++] = m_ReusableFaceColor.x;
		m_ColorBufferData[m_ColorBufferIndex++] = m_ReusableFaceColor.y;
		m_ColorBufferData[m_ColorBufferIndex++] = m_ReusableFaceColor.z;
	}


	static float randf() {
		return (float)(rand() % 1000) / 1000.0f;
	}

	void Chunk::build()
	{

		int x;
		int y;
		int z;
		glm::vec3 offset = glm::vec3();
		for (x = 0; x < CHUNK_SIZE; x++)
		{
			for (y = 0; y < CHUNK_SIZE; y++)
			{
				for (z = 0; z < CHUNK_SIZE; z++)
				{
					if (isBlockAir(x, y, z))
						continue;

					m_ReusableFaceColor = glm::vec3(randf(), randf(), randf());
					offset.x = x;
					offset.y = y;
					offset.z = z;
					m_ReusableBlockTranslation = m_ChunkOffset + offset;

					if (isBlockSolid(x, y, z - 1) == false)
						addFrontFace();

					if (isBlockSolid(x + 1, y, z) == false)
						addRightFace();

					if (isBlockSolid(x, y, z + 1) == false)
						addBackFace();

					if (isBlockSolid(x - 1, y, z) == false)
						addLeftFace();

					if (isBlockSolid(x, y - 1, z) == false)
						addBottomFace();

					if (isBlockSolid(x, y + 1, z) == false)
						addTopFace();



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
		if (index < 0 || index >= CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)
			return 0;
		return m_Blocks[index];
	}

	uint8_t Chunk::getBlockIdOfPosition(int localX, int localY, int localZ)
	{
		int index = localX + localY * CHUNK_SIZE + localZ * CHUNK_SIZE * CHUNK_SIZE;
		if (index < 0 || index >= CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)
			return 0;
		return m_Blocks[index];
	}

	void Chunk::setBlockAt(int localX, int localY, int localZ, uint8_t blockId)
	{
		int index = localX + localY * CHUNK_SIZE + localZ * CHUNK_SIZE * CHUNK_SIZE;
		if (index < 0 || index >= CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)
			return;
		m_Blocks[index] = blockId;
	}

	glm::vec3 Chunk::getPositionOffset()
	{
		return m_ChunkOffset;
	}

	bool Chunk::isBlockAir(int localX, int localY, int localZ)
	{
		return getBlockIdOfPosition(localX, localY, localZ) == 0;
	}

	bool Chunk::isBlockSolid(int localX, int localY, int localZ)
	{
		//TODO Later check on the actual block reference to see if the given block is opaque or not
		return getBlockIdOfPosition(localX, localY, localZ) > 0;
	}

}
