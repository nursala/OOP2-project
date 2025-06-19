#pragma once
#include "StatesInc/State.h"
#include <memory>

template<typename T>
class AttackingState : public State<T> {
public:
    void enter(T& character) override {};
    void update(T& character, float dt) override;

    virtual std::unique_ptr<State<T>> handleInput(T& entity) = 0;
};

template<typename T>
void AttackingState<T>::update(T& character, float dt) {
	character.shoot(dt);
}
