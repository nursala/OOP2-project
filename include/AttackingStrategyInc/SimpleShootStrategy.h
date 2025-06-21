#pragma once
#include "AttackingStrategyInc/AttakStrategy.h"

class SimpleShootStrategy : public AttackStrategy {
public:
    void attack(Character& character, float deltaTime) override;
};