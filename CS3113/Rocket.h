#ifndef ROCKET_H
#define ROCKET_H

#include "Block.h"
#include "Entity.h"

class Rocket : public Entity {
private:
    bool mFlying = false;
    bool mCrashed = false;
    bool mLanded = false;
    float mFuel = 5000.0f;
    Entity* mTrail = nullptr;

public:
    Rocket();
    Rocket(Vector2 position, Vector2 scale, const char* textureFilepath);
    Rocket(Vector2 position, Vector2 scale, const char* textureFilepath, TextureType textureType,
           Vector2 spriteSheetDimensions, std::map<Direction, std::vector<int>> animationAtlas);

    void update(float deltaTime, Block* collidableEntities, int numEntities);
    void turnRight();
    void turnLeft();
    void setFlying(bool isFlying);
    bool getFlying();
    bool isCrashed();
    bool isOutOfBounds(float screenWidth, float screenHeight);
    bool isLanded();
    void setFuel(float newFuel);
    float getFuel();

    Entity* getTrail();
    void setTrail(Entity* newTrail);
};

#endif
