#pragma once
#include "AttackingStrategyInc/AttakStrategy.h"

class SimpleShootStrategy : public AttackStrategy {
public:
    bool attack(Character& character) override;
};