#include "StatesInc/ChasingState.h"
#include "StatesInc/AttacingState.h"
#include "GameObject/Enemy.h"
#include "iostream"

void ChasingState::update(Enemy& enemy, float dt) {
	if (!enemy.isPlayerVisible()) {
		enemy.moveToPlayer(dt);
	}
}

std::unique_ptr<State<Enemy>> ChasingState::handleInput(Enemy& enemy) {

    if (enemy.isPlayerVisible() && enemy.distanceToPlayer() < enemy.getShootingRange()) {
        return std::make_unique<AttackingState>();
    }
    return nullptr;
}
