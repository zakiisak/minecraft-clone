#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/vec4.hpp>

namespace Game {

	enum BlockFace : uint8_t {
		BACK = 0,
		RIGHT = 1,
		FRONT = 2,
		LEFT = 3,
		BOTTOM = 4,
		TOP = 5
	};

	class Block {
	public:
		static Block* blocks[256];
		static void loadBlocks();

		bool isSolid();
		bool isOpaque();
		glm::vec3 getColor();
		glm::vec4 getTexCoord(BlockFace face);
		void setTexCoord(BlockFace face, glm::vec4 texCoord);
	private:
		bool m_Solid;
		bool m_Opaque = true;
		glm::vec3 m_Color;
		glm::vec4 m_TexCoords[6];
	};
}