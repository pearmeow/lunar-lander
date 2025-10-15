#ifndef ROCKET_H
#define ROCKET_H

#include "Entity.h"

class Rocket : public Entity {
public:
    Rocket();
    Rocket(Vector2 position, Vector2 scale, const char* textureFilepath);
    Rocket(Vector2 position, Vector2 scale, const char* textureFilepath, TextureType textureType,
           Vector2 spriteSheetDimensions, std::map<Direction, std::vector<int>> animationAtlas);

    void update(float deltaTime, Entity* collidableEntities, int numEntities, bool isFlying);
    void moveRight();
    void moveLeft();
};

#endif
