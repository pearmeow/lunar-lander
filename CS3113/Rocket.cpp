#include "Rocket.h"

#include <cmath>

Rocket::Rocket() : Entity() {
}

Rocket::Rocket(Vector2 position, Vector2 scale, const char* textureFilepath)
    : Entity(position, scale, textureFilepath) {
}

Rocket::Rocket(Vector2 position, Vector2 scale, const char* textureFilepath, TextureType textureType,
               Vector2 spriteSheetDimensions, std::map<Direction, std::vector<int>> animationAtlas)
    : Entity(position, scale, textureFilepath, textureType, spriteSheetDimensions, animationAtlas) {
}

void Rocket::update(float deltaTime, Entity* collidableEntities, int numEntities, bool isFlying) {
    Vector2 newAcc = getAcceleration();
    if (isFlying) {
        newAcc.x = 40.0f * std::sin(3.14f * getAngle() / 180.0f);
        newAcc.y = -40.0f * std::cos(3.14f * getAngle() / 180.0f) + 10.0f;
    } else {
        newAcc.y = 10.0f;
        newAcc.x = 0.0f;
    }
    setAcceleration(newAcc);
    Entity::update(deltaTime, collidableEntities, numEntities);
}

void Rocket::moveLeft() {
    if (getAngle() <= 0.0f) {
        setAngle(360.0f);
    } else {
        setAngle(getAngle() - 2.0f);
    }
}

void Rocket::moveRight() {
    if (getAngle() >= 360.0f) {
        setAngle(0.0f);
    } else {
        setAngle(getAngle() + 2.0f);
    }
}
