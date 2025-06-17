#include "StatesInc/AttacingState.h"
#include "StatesInc/ChasingState.h"
#include "GameObject/Enemy.h"
#include "iostream"

void AttackingState::update(Enemy& enemy, float dt) {
    enemy.shootAtPlayer(dt); 
}

std::unique_ptr<State<Enemy>> AttackingState::handleInput(Enemy& enemy) {
    if (!enemy.isPlayerVisible() || enemy.distanceToPlayer() > enemy.getShootingRange()) {
        return std::make_unique<ChasingState>();
    }
    return nullptr;
}
