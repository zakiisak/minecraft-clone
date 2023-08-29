#include "block.h"
namespace Game {

    static void setTexCoordsOnBlockFromIndex(Block* block, int index)
    {
        //Texture size is 256, and unit texture size is 16x16 => 256 / 16 = 16
        int x = index % 16;
        int y = index / 16;

        float u = x * 16.0f / 256.0f;
        float v = y * 16.0f / 256.0f;
        float size = 16.0f / 256.0f;

        for(int i = 0; i < 6; i++)
            block->setTexCoord((BlockFace) i, glm::vec4(u, v, size, size));
    }


    Block* Block::blocks[256];

    void Block::loadBlocks()
    {
        Block* dirt = new Block();
        setTexCoordsOnBlockFromIndex(dirt, 1);
        dirt->setTexCoord(BlockFace::TOP, glm::vec4(32.0f / 256.0f, 0, 16.0f / 256.0f, 16.0f / 256.0f));
        dirt->setTexCoord(BlockFace::FRONT, glm::vec4(48.0f / 256.0f, 0, 16.0f / 256.0f, 16.0f / 256.0f));
        dirt->setTexCoord(BlockFace::BACK, glm::vec4(48.0f / 256.0f, 0, 16.0f / 256.0f, 16.0f / 256.0f));
        dirt->setTexCoord(BlockFace::LEFT, glm::vec4(48.0f / 256.0f, 0, 16.0f / 256.0f, 16.0f / 256.0f));
        dirt->setTexCoord(BlockFace::RIGHT, glm::vec4(48.0f / 256.0f, 0, 16.0f / 256.0f, 16.0f / 256.0f));
        blocks[1] = dirt;

        Block* sand = new Block();
        setTexCoordsOnBlockFromIndex(sand, 4);
        blocks[2] = sand;
    }

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
    glm::vec4 Block::getTexCoord(BlockFace face)
    {
        return m_TexCoords[face];
    }

    void Block::setTexCoord(BlockFace face, glm::vec4 texCoord)
    {
        m_TexCoords[face] = texCoord;
    }

}
