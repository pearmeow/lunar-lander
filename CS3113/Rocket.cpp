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

void Rocket::update(float deltaTime, Block* collidableBlocks, int numEntities) {
    Vector2 newAcc = getAcceleration();
    if (mFlying && mFuel > 0.0f) {
        newAcc.x = 40.0f * std::sin(3.14f * getAngle() / 180.0f);
        newAcc.y = -40.0f * std::cos(3.14f * getAngle() / 180.0f) + 10.0f;
        mFuel -= 250.0f * deltaTime;
        if (mFuel <= 0.0f) {
            mFuel = 0.0f;
        }
    } else {
        // gravity
        newAcc.y = 10.0f;

        // slowly drift to a stop
        newAcc.x = -1.0f * getVelocity().x / 3.0;
    }
    setAcceleration(newAcc);
    Entity::update(deltaTime, collidableBlocks, numEntities);
    for (size_t i = 0; i < numEntities; ++i) {
        if (Entity::isColliding(collidableBlocks + i)) {
            if (collidableBlocks[i].getType() == LOSE) {
                mCrashed = true;
            }
        }
    }
}

void Rocket::moveLeft() {
    if (getAngle() <= 0.0f) {
        setAngle(360.0f);
    } else {
        setAngle(getAngle() - 1.3f);
    }
}

void Rocket::moveRight() {
    if (getAngle() >= 360.0f) {
        setAngle(0.0f);
    } else {
        setAngle(getAngle() + 1.3f);
    }
}

void Rocket::setFlying(bool isFlying) {
    mFlying = isFlying;
}

bool Rocket::getFlying() {
    return mFlying;
}

void Rocket::setFuel(float newFuel) {
    mFuel = newFuel;
}

float Rocket::getFuel() {
    return mFuel;
}

bool Rocket::isCrashed() {
    return mCrashed;
}

bool Rocket::isOutOfBounds(float screenWidth, float screenHeight) {
    if (getPosition().x + getScale().x < 0) {
        return true;
    }
    if (getPosition().y + getScale().y < 0) {
        return true;
    }
    if (getPosition().y - getScale().y > screenHeight) {
        return true;
    }
    if (getPosition().x - getScale().x > screenWidth) {
        return true;
    }
    return false;
}

bool Rocket::isLanded() {
    return mLanded;
}
