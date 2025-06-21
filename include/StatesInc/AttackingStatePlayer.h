#pragma once

#include "StatesInc/AttackingState.h"
#include "GameObject/Player.h"
#include <memory>

class AttackingStatePlayer : public AttackingState<Player> {
public:
    std::unique_ptr<State> handleInput(Character& character) override;
};
