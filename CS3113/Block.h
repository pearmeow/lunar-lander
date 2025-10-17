#ifndef BLOCK_H
#define BLOCK_H

#include "Entity.h"

enum BlockType { LOSE, WIN };

class Block : public Entity {
private:
    BlockType theType = LOSE;

public:
    Block();
    Block(Vector2 position, Vector2 scale, const char* textureFilepath);
    Block(Vector2 position, Vector2 scale, const char* textureFilepath, TextureType textureType,
          Vector2 spriteSheetDimensions, std::map<Direction, std::vector<int>> animationAtlas);

    void moveUp();
    void moveDown();
};

#endif
