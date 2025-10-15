#ifndef ROCKET_H
#define ROCKET_H

#include "Entity.h"

class Rocket : public Entity {
private:
    bool mFlying = false;

public:
    Rocket();
    Rocket(Vector2 position, Vector2 scale, const char* textureFilepath);
    Rocket(Vector2 position, Vector2 scale, const char* textureFilepath, TextureType textureType,
           Vector2 spriteSheetDimensions, std::map<Direction, std::vector<int>> animationAtlas);

    void update(float deltaTime, Entity* collidableEntities, int numEntities);
    void moveRight();
    void moveLeft();
    void setFlying(bool isFlying);
    bool getFlying();
};

#endif
