#pragma once

#include "MoveInfo.h"

class Entity;

class MoveStrategy {
public:
    virtual ~MoveStrategy() = default;
    virtual MoveInfo move(Entity& entity, float deltaTime) = 0;
};