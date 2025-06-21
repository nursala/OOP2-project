#include "StatesInc/ChasingState.h"
#include "StatesInc/AttackingStateEnemy.h"
#include "GameObject/Enemy.h"

std::unique_ptr<State> ChasingState::handleInput(Character& character) {
    Enemy& enemy = static_cast<Enemy&>(character);

    if (enemy.isPlayerVisible() && enemy.distanceToPlayer() < enemy.getWeapon()->getShootingRange()) {
        return std::make_unique<AttackingStateEnemy>();
    }

    return nullptr;
}
