#pragma once
#include "AttackingStrategyInc/AttakStrategy.h"

class SimpleShootStrategy : public AttackStrategy {
public:
    void attack(Enemy& enemy, float deltaTime) override;
};