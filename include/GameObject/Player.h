#pragma once

#include "GameObject/Entity.h"

class Player : public Entity {
public:
    Player(b2World& world);

    void update(float deltaTime) override;
};
