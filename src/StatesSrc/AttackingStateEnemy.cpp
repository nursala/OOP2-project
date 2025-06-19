#include "StatesInc/AttackingStateEnemy.h"
#include "StatesInc/ChasingState.h"
#include "GameObject/Enemy.h"
#include "iostream"


std::unique_ptr<State<Enemy>> AttackingStateEnemy::handleInput(Enemy& enemy) {
    if (!enemy.isPlayerVisible() || enemy.distanceToPlayer() > enemy.getShootingRange()) {
        return std::make_unique<ChasingState>();
    }
    return nullptr;
}
