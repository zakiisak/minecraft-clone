#pragma once
#include <glm/ext/vector_float3.hpp>

namespace Game {
	class Block {
	public:
		static Block blocks[256];

		bool isSolid();
		bool isOpaque();
		glm::vec3 getColor();
	private:
		bool m_Solid;
		bool m_Opaque;
		glm::vec3 m_Color;
	};
}