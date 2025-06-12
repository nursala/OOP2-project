#pragma once

#include "StatesInc/State.h"
#include "GameObject/Player.h"

class WalkingStatePlayer : public State<Player> {
public:
    void enter(Player& player) override;
    void update(Player& player, float deltaTime) override;
    std::unique_ptr<State<Player>> handleInput(Player& player) override;
};
