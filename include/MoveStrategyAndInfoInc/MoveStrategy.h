#pragma once

#include "MoveInfo.h"


class Character;

class MoveStrategy {
public:
    virtual ~MoveStrategy() = default;
    virtual MoveInfo move(Character& character, float deltaTime) = 0;
};