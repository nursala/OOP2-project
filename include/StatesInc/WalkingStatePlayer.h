#pragma once

#include "StatesInc/WalkingState.h"
#include "GameObject/Player.h"

class WalkingStatePlayer : public WalkingState<Player> {
public:
    std::unique_ptr<State<Player>> handleInput(Player& player) override;
};
