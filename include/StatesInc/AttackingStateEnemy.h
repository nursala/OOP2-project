#pragma once

#include "StatesInc/AttackingState.h"
#include "GameObject/Enemy.h"
#include <memory>

class AttackingStateEnemy : public AttackingState<Enemy> {
public:
    std::unique_ptr<State> handleInput(Character& character) override;
};
