#pragma once
#include "StatesInc/AttackingState.h"
#include <memory>
#include "GameObject/Enemy.h"

class AttackingStateEnemy: public AttackingState<Enemy> {
public:
    std::unique_ptr<State<Enemy>> handleInput(Enemy& enemy) override;
};
