#pragma once

#include "StatesInc/State.h"
#include "GameObject/Character.h"
#include "WeaponInc/Weapon.h"
#include <memory>
#include <iostream>

template<typename T>
class AttackingState : public State {
public:
    void enter(Character&) override {};
    void update(Character&, float) override;
    virtual std::unique_ptr<State> handleInput(Character&) override = 0;
};

template<typename T>
void AttackingState<T>::update(Character& character, float dt) {
    T& specific = static_cast<T&>(character);
    specific.shoot(dt);
}
