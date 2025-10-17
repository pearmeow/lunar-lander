#include "Block.h"

Block::Block() : Entity() {
}

Block::Block(Vector2 position, Vector2 scale, const char* textureFilepath)
    : Entity(position, scale, textureFilepath) {
}

Block::Block(Vector2 position, Vector2 scale, const char* textureFilepath, TextureType textureType,
             Vector2 spriteSheetDimensions, std::map<Direction, std::vector<int>> animationAtlas)
    : Entity(position, scale, textureFilepath, textureType, spriteSheetDimensions, animationAtlas) {
}

void Block::moveUp() {
    setAcceleration({0.0f, -10.0f});
}

void Block::moveDown() {
    setAcceleration({0.0f, 10.0f});
}

BlockType Block::getType() {
    return mType;
}

void Block::setType(BlockType newType) {
    mType = newType;
}
