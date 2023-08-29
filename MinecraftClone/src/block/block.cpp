#include "block.h"
namespace Game {

    Block Block::blocks[256];

    bool Block::isSolid()
    {
        return m_Solid;
    }

    bool Block::isOpaque()
    {
        return m_Opaque;
    }

    glm::vec3 Block::getColor()
    {
        return m_Color;
    }
}
