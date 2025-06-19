#include "StatesInc/AttackingStateEnemy.h"
#include "StatesInc/ChasingState.h"
#include "GameObject/Enemy.h"
#include <iostream>

std::unique_ptr<State> AttackingStateEnemy::handleInput(Character& character) {
    Enemy& enemy = static_cast<Enemy&>(character);

    if (!enemy.isPlayerVisible() || enemy.distanceToPlayer() > enemy.getShootingRange()) {
        return std::make_unique<ChasingState>();
    }
    return nullptr;
}
