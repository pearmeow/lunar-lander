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
    Entity::update(deltaTime, collidableEntities, numEntities);
    Vector2 newAcc = getAcceleration();
    if (isFlying) {
        newAcc.x -= 2000.0f * std::sin(getAngle()) * deltaTime;
        newAcc.y -= 2000.0f * std::cos(getAngle()) * deltaTime;
    }
    newAcc.y += 1000.00f * deltaTime;
    setAcceleration(newAcc);
}
