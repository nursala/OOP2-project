#include "StatesInc/AttackingStateEnemy.h"
#include "StatesInc/ChasingState.h"
#include "GameObject/Enemy.h"
#include "GameObject/Character.h"
#include <iostream>

std::unique_ptr<State> AttackingStateEnemy::handleInput(Character& character) {
   

    if (!character.getTargetsss())
    {
        return nullptr;
    }
    else
    {
        return std::make_unique<ChasingState>();
    }
}
