#pragma once

#include <StatesInc/State.h>
#include <MoveStrategyAndInfoInc/MoveInfo.h>

class WalkingState : public State {
public:
    void enter(Character&) override {};
    void update(Character&, float) override;
    std::unique_ptr<State> handleInput(Character&) override;
};

