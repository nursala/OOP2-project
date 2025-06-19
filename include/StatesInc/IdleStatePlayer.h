#pragma once

#include "StatesInc/State.h"
#include <memory>

class IdleStatePlayer : public State {
public:
    void enter(Character& character) override;
    void update(Character& character, float deltaTime) override;
    std::unique_ptr<State> handleInput(Character& character) override;
};
