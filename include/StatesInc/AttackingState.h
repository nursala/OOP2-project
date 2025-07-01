#pragma once

#include "StatesInc/State.h"
#include "GameObject/Character.h"
#include <memory>

class AttackingState : public State {
public:
    void update(Character&, float) override;
    std::unique_ptr<State> handleInput(Character&) override;
};


