#include "StatesInc/ChasingState.h"
#include "StatesInc/AttackingStateEnemy.h"
#include "GameObject/Enemy.h"

std::unique_ptr<State> ChasingState::handleInput(Character& character) {
        return std::make_unique<AttackingStateEnemy>();
}
