#ifndef ENTITY_H
#define ENTITY_H

#include "cs3113.h"

enum Direction { LEFT, UP, RIGHT, DOWN };  // For walking
enum EntityStatus { ACTIVE, INACTIVE };

class Entity {
private:
    Vector2 mPosition;
    Vector2 mMovement;
    Vector2 mVelocity;
    Vector2 mAcceleration;

    Vector2 mScale;
    Vector2 mColliderDimensions;

    Texture2D mTexture;
    TextureType mTextureType;
    Vector2 mSpriteSheetDimensions;

    std::map<Direction, std::vector<int>> mAnimationAtlas;
    std::vector<int> mAnimationIndices;
    Direction mDirection;
    int mFrameSpeed;

    int mCurrentFrameIndex = 0;
    float mAnimationTime = 0.0f;

    bool mIsJumping = false;
    float mJumpingPower = 0.0f;

    int mSpeed;
    float mAngle;

    bool mIsCollidingTop = false;
    bool mIsCollidingBottom = false;
    bool mIsCollidingRight = false;
    bool mIsCollidingLeft = false;

    EntityStatus mEntityStatus = ACTIVE;

    bool isColliding(Entity* other) const;
    void checkCollisionY(Entity* collidableEntities, int collisionCheckCount);
    void checkCollisionX(Entity* collidableEntities, int collisionCheckCount);
    void resetColliderFlags() {
        mIsCollidingTop = false;
        mIsCollidingBottom = false;
        mIsCollidingRight = false;
        mIsCollidingLeft = false;
    }

    void animate(float deltaTime);

public:
    static constexpr int DEFAULT_SIZE = 250;
    static constexpr int DEFAULT_SPEED = 200;
    static constexpr int DEFAULT_FRAME_SPEED = 14;
    static constexpr float Y_COLLISION_THRESHOLD = 0.5f;

    Entity();
    Entity(Vector2 position, Vector2 scale, const char* textureFilepath);
    Entity(Vector2 position, Vector2 scale, const char* textureFilepath, TextureType textureType,
           Vector2 spriteSheetDimensions, std::map<Direction, std::vector<int>> animationAtlas);
    ~Entity();

    void update(float deltaTime, Entity* collidableEntities, int collisionCheckCount);
    void render();
    void normaliseMovement();

    void jump();
    void activate();
    void deactivate();
    void displayCollider();

    bool isActive();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void resetMovement();

    Vector2 getPosition() const;
    Vector2 getMovement() const;
    Vector2 getVelocity() const;
    Vector2 getAcceleration() const;
    Vector2 getScale() const;
    Vector2 getColliderDimensions() const;
    Vector2 getSpriteSheetDimensions() const;
    Texture2D getTexture() const;
    TextureType getTextureType() const;
    Direction getDirection() const;
    int getFrameSpeed() const;
    float getJumpingPower() const;
    bool isJumping() const;
    int getSpeed() const;
    float getAngle() const;

    bool isCollidingTop() const;
    bool isCollidingBottom() const;

    std::map<Direction, std::vector<int>> getAnimationAtlas() const;

    void setPosition(Vector2 newPosition);
    void setMovement(Vector2 newMovement);
    void setAcceleration(Vector2 newAcceleration);
    void setScale(Vector2 newScale);
    void setTexture(const char* textureFilepath);
    void setColliderDimensions(Vector2 newDimensions);
    void setSpriteSheetDimensions(Vector2 newDimensions);
    void setSpeed(int newSpeed);
    void setFrameSpeed(int newSpeed);
    void setJumpingPower(float newJumpingPower);
    void setAngle(float newAngle);
};

#endif  // ENTITY_CPP
