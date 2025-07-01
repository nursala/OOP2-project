#pragma once

#include <StatesInc/State.h>

class WalkingState : public State {
public:
    void update(Character&, float) override;
    std::unique_ptr<State> handleInput(Character&) override;
};

