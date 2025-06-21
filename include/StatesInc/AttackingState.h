#pragma once

#include "StatesInc/State.h"
#include <memory>

template<typename T>
class AttackingState : public State {
public:
    void enter(Character& character) override {};
    void update(Character& character, float dt) override;
    virtual std::unique_ptr<State> handleInput(Character& character) override = 0;
};

template<typename T>
void AttackingState<T>::update(Character& character, float dt) {
    T& specific = static_cast<T&>(character);
    specific.shoot(dt);
}
