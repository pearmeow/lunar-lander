#ifndef ROCKET_H
#define ROCKET_H

#include "Entity.h"

class Rocket : public Entity {
    void update(float deltaTime, Entity* collidableEntities, int numEntities) override;
};

#endif
