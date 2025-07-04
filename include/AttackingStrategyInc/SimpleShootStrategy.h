#pragma once

//======================================================
// Description:   A basic attack strategy that causes a 
//                character to shoot directly at its target.
//======================================================

#include "AttackingStrategyInc/AttakStrategy.h"

class SimpleShootStrategy : public AttackStrategy {
public:
    // Executes the shooting behavior for the character.
    bool attack(Character& character) override;
};
